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


#ifndef C_CONTAINER_INTERNAL_H
#define C_CONTAINER_INTERNAL_H

#include "c-container.h"
// Linked List

LinkedListNode *_allocInitLinkedListNode(
	LinkedListNode *node, int key, void *value
);

void _freeLinkedListNode(LinkedListNode *node);

LinkedListNode **_getRefKeyLinkedList(LinkedList *out, int key);

LinkedListNode **_getRefIndexLinkedList(LinkedList *out, size_t index);

int _popNodeLinkedList(LinkedList *out, LinkedListNode **ref);

// Double Linked List

DoubleLinkedListNode *_allocInitDoubleLinkedListNode(
	DoubleLinkedListNode *node, int key, void *value
);

void _freeDoubleLinkedListNode(DoubleLinkedListNode *node);

DoubleLinkedListNode *_extractNodeDoubleLinkedList(
	LinkedList *out, DoubleLinkedListNode *node
);

// Hash Table

size_t _hashFunction(HashTable *in, size_t key);

HashTableNode *_extractNodeHashTable(HashTable *out, HashTableNode *node);

HashTableNode *_insertNodeHashTable(HashTable *out, HashTableNode *node);

#endif // C_CONTAINER_H
