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

DoubleLinkedListNode *_allocInitDoubleLinkedListNode(
	DoubleLinkedListNode *node, int key, void *value
) {
	if (node == NULL) {
		node = malloc(sizeof(struct DoubleLinkedListNode));
	}
	assert(node != NULL);

	_allocInitLinkedListNode((LinkedListNode *)node, key, value);
	node->last = NULL;

	return node;
}

void allocInitDoubleLinkedList(DoubleLinkedList *out)
{
	allocInitLinkedList(out);
}

void freeDoubleLinkedList(DoubleLinkedList *out)
{
	freeLinkedList(out);
}

DoubleLinkedListNode *insertNodeDoubleLinkedList(
	DoubleLinkedList *out, DoubleLinkedListNode *node
) {
	node->last = (DoubleLinkedListNode *)out->last;

	insertNodeLinkedList(out, (LinkedListNode*) node);

	return node;
}

DoubleLinkedListNode *insertKeyDoubleLinkedList(
	DoubleLinkedList *out, int key, void *value
) {
	DoubleLinkedListNode *node
		= _allocInitDoubleLinkedListNode(NULL, key, value);
	assert(node != NULL);

	return insertNodeDoubleLinkedList(out, node);
}

DoubleLinkedListNode *getKeyDoubleLinkedList(DoubleLinkedList *out, int key)
{
	return (DoubleLinkedListNode *)getKeyLinkedList(out, key);
}

DoubleLinkedListNode *getIndexDoubleLinkedList(
	DoubleLinkedList *out, size_t index
) {
	return (DoubleLinkedListNode *) getIndexLinkedList(out, index);
}

int _popNodeDoubleLinkedList(DoubleLinkedList *out, DoubleLinkedListNode *node)
{
	if (node == NULL) {
		return 0;
	}

	DoubleLinkedListNode *clist = (DoubleLinkedListNode *)out->list;
	DoubleLinkedListNode *clast = (DoubleLinkedListNode *)out->last;

	if (clist == node) {
		// Is first node
		assert(node->last == NULL);
		out->list = node->next;
		((DoubleLinkedListNode *)out->list)->last = NULL;
	} else if (clast == node) {
		assert(node->next == NULL);
		clast = node->last;

		assert((DoubleLinkedListNode *)clast->next == node);
		out->last->next = NULL;
	} else {
		assert(node->last != NULL);
		assert(node->next != NULL);
		assert(node->last->next == (LinkedListNode *) node);
		assert(((DoubleLinkedListNode *)node->next)->last == node);

		node->last->next = node->next;
		((DoubleLinkedListNode *)node->next)->last = node->last;
	}

	_freeLinkedListNode((LinkedListNode *) node);

	out->entries--;
	return 1;
}

int popKeyDoubleLinkedList(DoubleLinkedList *out, int key)
{
	DoubleLinkedListNode *node = getKeyDoubleLinkedList(out, key);
	return _popNodeDoubleLinkedList(out, node);
}

int popIndexDoubleLinkedList(DoubleLinkedList *out, size_t index)
{
	DoubleLinkedListNode *node = getIndexDoubleLinkedList(out, index);
	return _popNodeDoubleLinkedList(out, node);
}
