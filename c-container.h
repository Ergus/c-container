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


#ifndef C_CONTAINER_H
#define C_CONTAINER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



// Linked List ===================================================================

struct LinkedListNode {
	// Node for hash table (hash array + linked list to handle collision) and
	// access list (double linked list to remove and add node)
	int key;
	void *value;

	// Single linked list entries (handle hash collisions)
	struct LinkedListNode *next;
};

struct LinkedList {
	size_t entries;
	int copy;

	// This is the array for the hash table.
	struct LinkedListNode *list;
	struct LinkedListNode *last;
};

void allocInitLinkedList(struct LinkedList *out);
void freeLinkedList(struct LinkedList *out);

struct LinkedListNode *insertLinkedList(
	struct LinkedList *out, int key, void *value
);

struct LinkedListNode *getKeyLinkedList(const struct LinkedList *out, int key);
struct LinkedListNode *getIndexLinkedList(
	const struct LinkedList *out, size_t index
);

#endif // C_CONTAINER_H
