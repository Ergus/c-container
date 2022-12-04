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

size_t _hashFunction(HashTable *in, size_t key)
{
	return key % in->N;
}

void allocInitHashTable(HashTable *out, size_t N)
{
	out->entries = 0;
	out->N = N;

	out->table = malloc(N *sizeof(DoubleLinkedList));

	for (size_t i = 0; i < N; ++i) {
		allocInitDoubleLinkedList(&out->table[i]);
	}
}

void freeHashTable(HashTable *out)
{
	for (size_t i = 0; i < out->N; ++i) {
		freeDoubleLinkedList(&out->table[i]);
	}

	free(out->table);
	out->N = 0;
	out->entries = 0;
}

HashTableNode *insertKeyHashTable(HashTable *out, int key, void *value)
{
	const size_t hash = _hashFunction(out, key);
	assert(hash < out->N);

	LinkedList *hashEntry = &out->table[hash];
	HashTableNode *node = getKeyDoubleLinkedList(hashEntry, key);

	if (node == NULL) {
		out->entries++;
		node = insertKeyDoubleLinkedList(hashEntry, key, value);
	} else {
		free(node->value);
		node->value = value;
	}

	return node;
}

HashTableNode *getKeyHashTable(HashTable *out, int key)
{
	const size_t hash = _hashFunction(out, key);
	assert(hash < out->N);

	return getKeyDoubleLinkedList(&out->table[hash], key);
}

int _popNodeHashTable(HashTable *out, HashTableNode *node)
{
	assert(node != NULL);
	assert(out->entries > 0);

	const size_t hash = _hashFunction(out, node->key);
	assert(hash < out->N);

	int removed = _popNodeDoubleLinkedList(&out->table[hash], node);
	assert(removed == 1);

	out->entries--;
	return removed;
}

int popKeyHashTable(HashTable *out, int key)
{
	const size_t hash = _hashFunction(out, key);
	assert(hash < out->N);

	int removed = popKeyDoubleLinkedList(&out->table[hash], key);
	out->entries -= removed;
	return removed;
}
