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

/*! \file
  \brief Header for c-container library

  This file contains the public functions for c-container library for final
  users
*/

#ifndef C_CONTAINER_H
#define C_CONTAINER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Linked List ===================================================================

/*!
  \defgroup list Simple Linked list
  \brief This is the simpler linker list and its functions
*/
//@{

//! Linked list node type
/*!
  This are the nodes included in the linked list
*/
typedef struct LinkedListNode {
	// Node for hash table (hash array + linked list to handle collision) and
	// access list (double linked list to remove and add node)
	int key;                      /*!< Node key LinkedListNode#key. */
	void *value;                  /*!< Node content LinkedListNode#value. */

	// Single linked list entries (handle hash collisions)
	struct LinkedListNode *next;  /*!< Pointer to the next element LinkedListNode#next. */
} LinkedListNode;

//! Linked list container
/*!
  This is the simple container for #LinkedListNode nodes.
*/
typedef struct LinkedList {
	size_t entries;     /*!< Counter for nodes of entries LinkedList#entries. */

	// This is the array for the hash table.
	LinkedListNode *list;   /*!< Start of the list LinkedList#list. */
	LinkedListNode *last;   /*!< Last node of the list LinkedList#last. */
} LinkedList;

//! Constructor for #LinkedList container
/*!
  \param[out] out Pointer to #LinkedList object to construct.
*/
void allocInitLinkedList(LinkedList *out);

//! Destructor for #LinkedList container
/*!
  \param[out] out Pointer to #LinkedList object to free.
*/
void freeLinkedList(LinkedList *out);

//! Insert node at the end of the #LinkedList O(1)
/*!
  \param[out] out Pointer to #LinkedList object.
  \param[in] node Pointer to #LinkedListNode to insert in the linked list.
  \return A pointer to the #LinkedListNode inserted (the same than node)
*/
LinkedListNode *insertNodeLinkedList(LinkedList *out, LinkedListNode *node);

//! Create #LinkedListNode and insert at the end of the #LinkedList O(1)
/*!
  \param[out] out Pointer to #LinkedList object.
  \param[in] key Value for key of new #LinkedListNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #LinkedListNode inserted.
*/
LinkedListNode *insertKeyLinkedList(LinkedList *out, int key, void *value);

//! Search for a node in the #LinkedList given a key with complexity O(n)
/*!
  When not node with this key is present, then return NULL

  \param[in] out Pointer to #LinkedList object.
  \param[in] key Value for key of node to search
  \return A #LinkedListNode pointer to the node or NULL.
*/
LinkedListNode *getKeyLinkedList(LinkedList *out, int key);

//! Search for a node on #LinkedList given the index complexity O(index)
/*!
  When the list contains less nodes than the index returns NULL

  \param[in] out Pointer to #LinkedList object.
  \param[in] index Positional index of interest
  \return A #LinkedListNode pointer to the node or NULL.
*/
LinkedListNode *getIndexLinkedList(LinkedList *out, size_t index);

//! Remove #LinkedListNode from #LinkedList given a key O(n)
/*!
  Remove a the first #LinkedListNode with a given key if exists

  \param[inout] out Pointer to #LinkedList object.
  \param[in] key Value for key of node to remove
  \return 1 when a #LinkedListNode was removed or 0 when no such node was found.
*/
int popKeyLinkedList(LinkedList *out, int key);

//! Remove #LinkedListNode from #LinkedList given its index O(index)
/*!
  Remove the #LinkedListNode at index if such node exists

  \param[inout] out Pointer to #LinkedList object.
  \param[in] index Positional index of interest
  \return 1 when a #LinkedListNode was removed or 0 when no such node was found.
*/
int popIndexLinkedList(LinkedList *out, size_t index);

//@}


// Double Linked List ==========================================================

/*!
  \defgroup double Double Linked list
  \brief This is the Double linker list and its functions
*/
//@{

//! Double linked list node type
/*!
  This is like a #LinkedListNode but includes an extra pointer to the element
  on the left. That improves performance on remove operations but add extra
  complexity to keep update the extra pointer. The implementation of this
  class implements an inheritance from the simple linked list.
*/
typedef struct DoubleLinkedListNode {
	struct LinkedListNode;
	struct DoubleLinkedListNode *last; /*!< Pointer to the previous element. */
} DoubleLinkedListNode;


typedef LinkedList DoubleLinkedList;

//! Constructor for #DoubleLinkedList container
/*!
  \param[out] out Pointer to #DoubleLinkedList object to construct.
*/
void allocInitDoubleLinkedList(DoubleLinkedList *out);

//! Destructor for #DoubleLinkedList container
/*!
  \param[out] out Pointer to #DoubleLinkedList object to free.
*/
void freeDoubleLinkedList(DoubleLinkedList *out);

//! Insert node at the end of the #DoubleLinkedList O(1)
/*!
  \param[out] out Pointer to #DoubleLinkedList object.
  \param[in] node Pointer to #DoubleLinkedListNode to insert in the #DoubleLinkedList.
  \return A pointer to the #DoubleLinkedListNode inserted (the same than node)
*/
DoubleLinkedListNode *insertNodeDoubleLinkedList(
	DoubleLinkedList *out, DoubleLinkedListNode *node);

//! Create #DoubleLinkedListNode and insert at the end of the #LinkedList O(1)
/*!
  \param[out] out Pointer to #DoubleLinkedList object.
  \param[in] key Value for key of new #DoubleLinkedListNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #DoubleLinkedListNode inserted.
*/
DoubleLinkedListNode *insertKeyDoubleLinkedList(
	DoubleLinkedList *out, int key, void *value
);


//! Search for a #DoubleLinkedListNode in the #DoubleLinkedList given a key with complexity O(n)
/*!
  When not #DoubleLinkedListNode with this key is present, then return NULL

  \param[in] out Pointer to #DoubleLinkedList object.
  \param[in] key Value for key of node to search
  \return A #DoubleLinkedListNode pointer to the node or NULL.
*/
DoubleLinkedListNode *getKeyDoubleLinkedList(DoubleLinkedList *out, int key);

//! Search for a #DoubleLinkedListNode on #DoubleLinkedList given the index complexity O(index)
/*!
  When the list contains less #DoubleLinkedListNode than the index this returns NULL

  \param[in] out Pointer to #DoubleLinkedList object.
  \param[in] index Positional index of interest
  \return A #DoubleLinkedList pointer to the node or NULL.
*/DoubleLinkedListNode *getIndexDoubleLinkedList(DoubleLinkedList *out, size_t index);

//! Remove #DoubleLinkedListNode from #DoubleLinkedList given a key O(n)
/*!
  Remove a the first #DoubleLinkedListNode with a given key if exists

  \param[inout] out Pointer to #DoubleLinkedList object.
  \param[in] key Value for key of #DoubleLinkedListNode to remove
  \return 1 when a #DoubleLinkedListNode was removed or 0 when no such node was found.
*/
int popKeyDoubleLinkedList(LinkedList *out, int key);

//! Remove #DoubleLinkedListNode from #DoubleLinkedList given its index O(index)
/*!
  Remove the #DoubleLinkedListNode at index if such node exists

  \param[inout] out Pointer to #DoubleLinkedList object.
  \param[in] index Positional index of interest
  \return 1 when a #DoubleLinkedListNode was removed or 0 when no such node was found.
*/
int popIndexDoubleLinkedList(LinkedList *out, size_t index);

//@}

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

// LRU Table =================================================================

// C inheritance emulation.  The LRU table is just a hash table which overlaps
// with a linked list.
typedef struct lruTableNode {
	HashTableNode;

	// Extend with the double linked list nodes
	struct lruTableNode *left, *right;
} lruTableNode;


typedef struct lruTable {
	struct HashTable;

	// Hash table with limited number of entries.
	size_t maxEntries;

	// Access list cache. needs two pointers to the first and last element.
	struct lruTableNode *accesList, *lastAccess;
} lruTable;

void allocInitlruTable(lruTable *out, size_t N);

void freelruTable(lruTable *out);
lruTableNode *insertKeylruTable(lruTable *out, int key, void *value);

lruTableNode *getKeylruTable(lruTable *out, int key);

#endif // C_CONTAINER_H
