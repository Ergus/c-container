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
#include <stdio.h>

#define NENTRIES 10

void printfunc(struct BinaryTreeNode *node, void *_ignore)
{
	printf("%d %d\n", node->key, *(int*)node->value);
}

int main()
{
	size_t values[] = {4, 5, 3, 128, 56, 57, 58, 55, 0, 1};

	struct BinaryTree list;
	allocInitBinaryTree(&list);

	// Insert 10 values and test
	printf("Insert 10 values\n");
	for (size_t i = 0; i < 10; ++i) {
		int *val = malloc(sizeof(int));
		*val = values[i];

		BinaryTreeNode *node = insertBinaryTree(&list, values[i], val);

		assert(node != 0);
		assert(node->key == values[i]);
		assert(*(int *)(node->value) == values[i]);
	}

	{   // Insert a repeated key element to test the collision solver code.
		int *val = malloc(sizeof(int));
		*val = 0;

		BinaryTreeNode *node = insertBinaryTree(&list, values[3], val);
		assert(node != 0);
		assert(node->key == values[3]);
		assert(*(int *)(node->value) == 0);

		*val = values[3];
	}

	// Check the 10 values by key
	printf("Check 10 values\n");
	for (size_t i = 0; i < 10; ++i) {
		BinaryTreeNode *node = getKeyBinaryTree(&list, values[i]);

		assert(node != NULL);
		assert(node->key == values[i]);
		assert(*(int *)(node->value) == values[i]);
	}

	printf("Check invalid keys\n");
	assert(getKeyBinaryTree(&list, NENTRIES * 10 + 1) == NULL);

	printf("Check dsf function");
	dsfBinaryTree(&list, printfunc, NULL);

	printf("Check bsf function");
	bsfBinaryTree(&list, printfunc, NULL);

	// Test the remove function.
	// Remove keys form font to use the most complex combinations
	printf("Check remove keys\n");
	for (size_t i = 0; i < 5; ++i) {
		assert(popKeyBinaryTree(&list, values[i]) == 1);

		for (size_t j = 0; j < 10; ++j) {
			BinaryTreeNode *node = getKeyBinaryTree(&list, values[j]);

			if (j <= i) {
				assert(node == NULL);
			} else {
				assert(node != NULL);
				assert(node->key == values[j]);
				assert(*(int *)(node->value) == values[j]);
			}
		}
	}

	assert(popKeyBinaryTree(&list, 2) == 0);

	freeBinaryTree(&list);

	return 0;
}
