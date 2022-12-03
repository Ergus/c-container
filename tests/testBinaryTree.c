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

	struct BinaryTree list;
	allocInitBinaryTree(&list);

	// Insert 10 values and test
	for (size_t i = 0; i < 10; ++i) {
		values[i] = rand() % (NENTRIES * 10);

		int *val = malloc(sizeof(int));
		*val = values[i];

		struct BinaryTreeNode *node = insertBinaryTree(&list, values[i], val);

		assert(node != 0);
		assert(node->key == values[i]);
		assert(*(int *)(node->value) == values[i]);
	}

	// Check the 10 values by key
	for (size_t i = 0; i < 10; ++i) {
		struct BinaryTreeNode *node = getKeyBinaryTree(&list, values[i]);

		assert(node != NULL);
		assert(node->key == values[i]);
		assert(*(int *)(node->value) == values[i]);
	}

	assert(getKeyBinaryTree(&list, NENTRIES * 10 + 1) == NULL);

	freeBinaryTree(&list);

	return 0;
}
