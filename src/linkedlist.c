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

// List Node ===================================================================

LinkedListNode *_allocInitLinkedListNode(
	LinkedListNode *node, int key, void *value
) {
	// Allocate and initialize a node. Sets value and set the references NULL.
	// this is like a constructor with new (because it calls malloc.)
	if (node == NULL) {
		node = malloc(sizeof(struct LinkedListNode));
	}

	node->key = key;
	node->value = value;

	node->next = NULL;

	return node;
}

void _freeLinkedListNode(LinkedListNode *node)
{
	// the value needs to be released as the node has its ownership
	free(node->value);
	free(node);
}

void allocInitLinkedList(LinkedList *out)
{
	out->entries = 0;

	out->list = NULL;
	out->last = NULL;
}

void freeLinkedList(LinkedList *out)
{
	LinkedListNode *it = out->list;
	while (it != NULL) {
		LinkedListNode *tmp = it;
		it = it->next;
		_freeLinkedListNode(tmp);
	}

	out->entries = 0;
}

LinkedListNode *insertNodeLinkedList(LinkedList *out, LinkedListNode *node)
{
	assert(node != NULL);

	if (out->last != NULL) {
		assert(out->list != NULL);
		out->last->next = node;
		out->last = node;
	} else {
		assert(out->list == NULL);
		out->list = node;
		out->last = node;
	}

	out->entries++;

	return node;
}

LinkedListNode *insertKeyLinkedList(LinkedList *out, int key, void *value)
{
	LinkedListNode *node = _allocInitLinkedListNode(NULL, key, value);
	assert(node != NULL);
	return insertNodeLinkedList(out, node);
}

LinkedListNode **_getRefKeyLinkedList(LinkedList *out, int key)
{
	LinkedListNode **ref = &out->list;
	for (; *ref != NULL && (*ref)->key != key; ref = &(*ref)->next);
	return ref;
}

LinkedListNode *getKeyLinkedList(LinkedList *out, int key)
{
	LinkedListNode **ref = _getRefKeyLinkedList(out, key);;
	return ref != NULL ? *ref : NULL;
}

LinkedListNode **_getRefIndexLinkedList(LinkedList *out, size_t index)
{
	if (index >= out->entries) {
		return NULL;
	}

	size_t counter = 0;
	LinkedListNode **ref = &out->list;
	for (; counter < index; ref = &(*ref)->next) {
		++counter;
	};

	return ref;
}

LinkedListNode *getIndexLinkedList(LinkedList *out, size_t index)
{
	LinkedListNode **ref = _getRefIndexLinkedList(out, index);
	return ref != NULL ? *ref : NULL;
}

int _popNodeLinkedList(LinkedList *out, LinkedListNode **ref)
{
	if (*ref == NULL) {
		return 0;
	}

	LinkedListNode *next = (*ref)->next;

	out->entries--;
	free(*ref);
	*ref = next;
	return 1;
}

int popKeyLinkedList(LinkedList *out, int key)
{
	LinkedListNode **ref = _getRefKeyLinkedList(out, key);
	return _popNodeLinkedList(out, ref);
}

int popIndexLinkedList(LinkedList *out, size_t index)
{
	LinkedListNode **ref = _getRefIndexLinkedList(out, index);
	return _popNodeLinkedList(out, ref);
}
