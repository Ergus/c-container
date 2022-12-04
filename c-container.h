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

typedef struct LinkedListNode {
	// Node for hash table (hash array + linked list to handle collision) and
	// access list (double linked list to remove and add node)
	int key;
	void *value;

	// Single linked list entries (handle hash collisions)
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
	size_t entries;

	// This is the array for the hash table.
	LinkedListNode *list;
	LinkedListNode *last;
} LinkedList;

void allocInitLinkedList(LinkedList *out);
void freeLinkedList(LinkedList *out);

LinkedListNode *insertNodeLinkedList(LinkedList *out, LinkedListNode *node);
LinkedListNode *insertKeyLinkedList(LinkedList *out, int key, void *value);

LinkedListNode *getKeyLinkedList(LinkedList *out, int key);
LinkedListNode *getIndexLinkedList(LinkedList *out, size_t index);

int popKeyLinkedList(LinkedList *out, int key);
int popIndexLinkedList(LinkedList *out, size_t index);

// Binary Tree =================================================================

typedef struct BinaryTreeNode {
	// Node for hash table (hash array + linked list to handle collision) and
	// access list (double linked list to remove and add node)
	int key;
	void *value;

	// Single linked list entries (handle hash collisions)
	struct BinaryTreeNode *parent;
	struct BinaryTreeNode *left;
	struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct BinaryTree {
	size_t entries;

	// This is the array for the hash table.
	BinaryTreeNode *tree;

	BinaryTreeNode *start;
	BinaryTreeNode *end;
} BinaryTree;

void allocInitBinaryTree(BinaryTree *out);
void freeBinaryTree(BinaryTree *out);

BinaryTreeNode *insertBinaryTree(BinaryTree *out, int key, void *value);

BinaryTreeNode *getKeyBinaryTree(BinaryTree *out, int key);

int popKeyBinaryTree(BinaryTree *out, int key);

// Hash Table =================================================================

typedef DoubleLinkedListNode HashTableNode;

typedef struct HashTable {
	size_t entries;
	size_t N;

	// This is the array for the hash table.
	DoubleLinkedList *table;
} HashTable;

void allocInitHashTable(HashTable *out, size_t N);
void freeHashTable(HashTable *out);

HashTableNode *insertKeyHashTable(HashTable *out, int key, void *value);

HashTableNode *getKeyHashTable(HashTable *out, int key);

int popKeyHashTable(HashTable *out, int key);

#endif // C_CONTAINER_H
