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

static BinaryTreeNode *_allocInitBinaryTree(
	struct BinaryTreeNode *node, int key, void *value
) {
	// Allocate and initialize a node. Sets value and set the references NULL.
	// this is like a constructor with new (because it calls malloc.)
	if (node == NULL) {
		node = malloc(sizeof(struct BinaryTreeNode));
	}

	node->key = key;
	node->value = value;

	node->left = NULL;
	node->right = NULL;

	return node;
}

static void _freeBinaryTreeNode(BinaryTreeNode *node)
{
	if (node == NULL){
		return;
	}

	if (node->left != NULL) {
		_freeBinaryTreeNode(node->left);
	}

	if (node->right != NULL) {
		_freeBinaryTreeNode(node->right);
	}

	free(node->value);
	free(node);
}

void allocInitBinaryTree(BinaryTree *out)
{
	out->entries = 0;
	out->tree = NULL;
	out->start = NULL;
	out->end = NULL;
}

void freeBinaryTree(BinaryTree *out)
{
	_freeBinaryTreeNode(out->tree);
}

BinaryTreeNode **_getSlotBinaryTree(BinaryTreeNode **root, int key)
{
	BinaryTreeNode **it = root;

	while (*it != NULL) {
		if (key > (*it)->key) {
			it = &((*it)->right);
		} else if (key < (*it)->key) {
			it = &((*it)->left);
		} else {
			// key == node->value;
			break;
		}
	}
	return it;
}

BinaryTreeNode *insertBinaryTree(BinaryTree *out, int key, void *value)
{
	BinaryTreeNode **it = _getSlotBinaryTree(&out->tree, key);

	if (*it == NULL) {
		*it = _allocInitBinaryTree(NULL, key, value);
		out->entries++;
	} else {
		free((*it)->value);
		(*it)->value = value;
	}

	return *it;
}

BinaryTreeNode *getKeyBinaryTree(BinaryTree *out, int key)
{
	BinaryTreeNode **it = _getSlotBinaryTree(&out->tree, key);
	return *it;
}


static int _removeKeyBinaryTree(BinaryTreeNode **root, int key)
{
	assert(root != NULL);
	assert(*root != NULL);

	BinaryTreeNode **it = _getSlotBinaryTree(root, key);

	if (*it == NULL) {
		return 0;
	}

	free((*it)->value);

	if ((*it)->left == NULL && (*it)->right == NULL) {
		free((*it));
		*it = NULL;
	} else if ((*it)->left == NULL || (*it)->right == NULL) {
		BinaryTreeNode *tmp = (*it)->left != NULL ? (*it)->left : (*it)->right;
		free((*it));
		*it = tmp;
	} else {
		BinaryTreeNode *tmp = (*it)->right;
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}

		(*it)->key = tmp->key;
		(*it)->value = tmp->value;
		tmp->value = NULL;   // free on NULL is save.

		int removed = _removeKeyBinaryTree(&(*it)->right, tmp->key);
		assert(removed == 1);
	}
	return 1;
}

int popKeyBinaryTree(BinaryTree *out, int key)
{
	int removed = _removeKeyBinaryTree(&(out->tree), key);
	out->entries -= removed;
	return removed;
}
