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

#ifdef NDEBUG
#error "Only Debug builds are supported"
#endif

#include "c-container.h"

#define NENTRIES 10

int main()
{
	size_t values[NENTRIES];

	LinkedList list;
	allocInitLinkedList(&list);

	// Insert 10 values and test
	for (size_t i = 0; i < 10; ++i) {
		values[i] = rand() % (NENTRIES * 10);

		int *val = malloc(sizeof(int));
		*val = values[i];

		LinkedListNode *node = insertLinkedList(&list, i, val);

		assert(node != 0);
		assert(node->key == i);
		assert(*(int *)(node->value) == values[i]);
	}

	// Check the 10 values by key
	for (size_t i = 0; i < 10; ++i) {
		LinkedListNode *node = getKeyLinkedList(&list, i);

		assert(node != NULL);
		assert(node->key == i);
		assert(*(int *)(node->value) == values[i]);
	}

	assert(getKeyLinkedList(&list, 10) == NULL);
	assert(getKeyLinkedList(&list, 15) == NULL);

	// Check the 10 values by index
	for (size_t i = 0; i < 10; ++i) {
		LinkedListNode *node = getIndexLinkedList(&list, i);

		assert(node != 0);
		assert(node->key == i);
		assert(*(int *)(node->value) == values[i]);
	}

	assert(getIndexLinkedList(&list, 10) == NULL);
	assert(getIndexLinkedList(&list, 15) == NULL);

	// Test popKeyLinkedList
	popKeyLinkedList(&list, 0);
	popKeyLinkedList(&list, 5);
	popKeyLinkedList(&list, 9);

	for (size_t i = 0; i < 10; ++i) {
		LinkedListNode *node = getKeyLinkedList(&list, i);

		if (i == 0 || i == 5 || i == 9) {
			assert(node == NULL);
		} else {
			assert(node != NULL);
			assert(node->key == i);
			assert(*(int *)(node->value) == values[i]);
		}
	}

	// Test remove index
	popIndexLinkedList(&list, 0);
	popIndexLinkedList(&list, 2);
	popIndexLinkedList(&list, 3);

	for (size_t i = 0; i < 10; ++i) {
		LinkedListNode *node = getIndexLinkedList(&list, i);

		if (i > 3) {
			assert(node == NULL);
		} else {
			assert(node != NULL);
		}
	}

	freeLinkedList(&list);

	return 0;
}
