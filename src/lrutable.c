/*
 * Copyright (C) 2022  Jimmy Aguilar Mena
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "c-container.h"
#include "c-container-internal.h"

// List Node ===================================================================

static lruTableNode* _allocInitlruTableNode(lruTableNode *node, int key, void *value)
{
	if (node == NULL) {
		node = malloc(sizeof(struct lruTableNode));
	}
	assert(node != NULL);

	_allocInitDoubleLinkedListNode((HashTableNode*) node, key, value);

	node->left = NULL;
	node->right = NULL;

	return node;
}

void allocInitlruTable(lruTable *out, size_t N)
{
	allocInitHashTable((HashTable *) out, N);

	out->maxEntries = N;
	out->accesList = NULL;
	out->lastAccess = NULL;
}

void freelruTable(lruTable *out)
{
	freeHashTable((HashTable *) out);

	out->maxEntries = 0;
	out->accesList = NULL;
	out->lastAccess = NULL;
}

void _disconnectlruTableNodeAccess(lruTable *in, lruTableNode *node)
{
	// Remove one node from the access and connect the adjacent ones.  The node
	// may be released individually, but this is not a perfect world and there
	// are race conditions.
	assert(node != NULL);

	if (node->left == NULL && node->right == NULL) {
		return;
	} else if (in->accesList == node) {     // it is the oldest access, so no left
		assert(node->left == NULL);
		in->accesList = node->right;
		in->accesList->left = NULL;
	} else if (in->lastAccess == node) { // it is the newer access, so no right
		assert(node->right == NULL);
		in->lastAccess = node->left;
		in->lastAccess->right = NULL;
	} else {
		node->left->right = node->right;
		node->right->left = node->left;
	}
	node->right = NULL;
	node->left = NULL;
}

void _registerNodeAccess(lruTable *in, lruTableNode *node)
{
	// This may be called every time a new node is accessed or when a value is
	// retrieved with the get function.
	if (in->lastAccess == NULL) {  // Registering the very first access
		assert(in->accesList == NULL);
		in->accesList = node;
		in->lastAccess = node;
	}

	// When it is the last access just exit, no changes needed
	if (in->lastAccess == node) {
		return;
	}

	in->lastAccess->right = node;
	node->left = in->lastAccess;
	in->lastAccess = node;
}

lruTableNode *insertlruTable(lruTable *out, int key, void *value)
{
	assert(out->entries <= out->maxEntries);
	HashTableNode *nodeUncasted = getKeyHashTable((HashTable *)out, key);

	lruTableNode *node = (lruTableNode *) nodeUncasted;

	if (node != NULL) {
		// Node exist, so update value only
		free(node->value);
		node->value = value;
		_disconnectlruTableNodeAccess(out, node);
	} else {

		if (out->entries == out->maxEntries) {
			// When full, remove the least recent access.
			_disconnectlruTableNodeAccess(out, out->accesList);

			// This performs an extra search
			int removed = popKeyHashTable(
				(HashTable *)out, out->accesList->key);
			assert(removed == 1);
			assert(out->entries == out->maxEntries - 1);
		}

		const size_t hash = _hashFunction((HashTable *)out, key);
		LinkedList *hashEntry = &out->table[hash];

		node = _allocInitlruTableNode(NULL, key, value);
		insertNodeDoubleLinkedList(hashEntry, (DoubleLinkedListNode *)node);
	}

	_registerNodeAccess(out, node);

	return node;
}
