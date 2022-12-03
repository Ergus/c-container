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

static struct BinaryTreeNode *_allocInitBinaryTree(
	struct BinaryTreeNode *node, int key, void *value
) {
	// Allocate and initialize a node. Sets value and set the references NULL.
	// this is like a constructor with new (because it calls malloc.)
	if (node == NULL) {
		node = malloc(sizeof(struct BinaryTreeNode));
	}

	node->key = key;
	node->value = value;

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static void _freeBinaryTreeNode(struct BinaryTreeNode *node)
{
	if (node->left != NULL) {
		_freeBinaryTreeNode(node->left);
	}

	if (node->right != NULL) {
		_freeBinaryTreeNode(node->right);
	}

	if (node->parent) {
		// if node has a parent set the pointer to me equal to NULL
		if (node->parent->key > node->key) {
			assert(node->parent->left == node);
			node->parent->left = NULL;
		} else {
			assert(node->parent->right == node);
			node->parent->right = NULL;
		}
	}

	free(node->value);
	free(node);
}

void allocInitBinaryTree(struct BinaryTree *out)
{
	out->entries = 0;
	out->tree = NULL;
	out->start = NULL;
	out->end = NULL;
}

void freeBinaryTree(struct BinaryTree *out)
{
	_freeBinaryTreeNode(out->tree);
}

struct BinaryTreeNode **_getSlotBinaryTree(struct BinaryTree *out, int key)
{
	struct BinaryTreeNode **it = &out->tree;

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

struct BinaryTreeNode *insertBinaryTree(
	struct BinaryTree *out, int key, void *value
) {
	struct BinaryTreeNode **it = _getSlotBinaryTree(out, key);

	if (*it == NULL) {
		*it = _allocInitBinaryTree(NULL, key, value);
		out->entries++;
	} else {
		free((*it)->value);
		(*it)->value = value;
	}

	return *it;
}

struct BinaryTreeNode *getKeyBinaryTree(struct BinaryTree *out, int key)
{
	struct BinaryTreeNode **it = _getSlotBinaryTree(out, key);
	return *it;
}
