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
  @{
*/

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

//! Create a #LinkedListNode and insert at the end of the #LinkedList O(1)
/*!
  \param[out] out Pointer to #LinkedList object.
  \param[in] key Value for key of new #LinkedListNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #LinkedListNode inserted.
*/
LinkedListNode *insertKeyLinkedList(LinkedList *out, int key, void *value);

//! Search for a node in the #LinkedList given a key with complexity O(n)
/*!
  When no node with this key is present, then return NULL

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

//!@}


// Double Linked List ==========================================================

/*!
  \defgroup double Double Linked list
  \brief This is the Double linker list and its functions
  @{
*/

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

//! Double linked list container implemented as a LinkedList with different nodes
/*!
  The contained is just a typedef for #LinkedList because all the functionalities
  and functions are very similar. The main difference is in the implementation
  side that reduces some complexities and simplifies the operation.
*/
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

//!@}

// Binary Tree =================================================================

/*!
  \defgroup tree Simple binary search tree
  \brief This is the binary tree container.
  @{
*/

//! Binary tree node type
/*!
  This is like a #LinkedListNode but includes two extra pointer to the element
  on the left (lower) and right (bigger) . This reduces the search complexity to 
  O(log(n)) but increases the cost to remove a node to O(n).
*/
typedef struct BinaryTreeNode {
	// Node for hash table (hash array + linked list to handle collision) and
	// access list (double linked list to remove and add node)
	int key;                      /*!< Node key BinaryTreeNode#key. */
	void *value;                  /*!< Node content BinaryTreeNode#value. */

	// Single linked list entries (handle hash collisions)
	struct BinaryTreeNode *left;   /*!< Left node (lower).*/
	struct BinaryTreeNode *right;  /*!< Right node (higher).*/
} BinaryTreeNode;

//! Binary tree container
/*!
  This is the container for #BinaryTreeNode nodes.
*/
typedef struct BinaryTree {
	size_t entries;  /*!< Counter for nodes of entries LinkedList#entries. */

	// This is the array for the hash table.
	BinaryTreeNode *tree;  /*!< Root node for the tree. */

	BinaryTreeNode *start; /*!< Pointer to first (lower) node. */
	BinaryTreeNode *end;   /*!< Pointer to last (higher) node. */
} BinaryTree;

//! Constructor for #BinaryTree container
/*!
  \param[out] out Pointer to #BinaryTree object to construct.
*/
void allocInitBinaryTree(BinaryTree *out);

//! Destructor for #BinaryTree container
/*!
  \param[out] out Pointer to #BinaryTree object to free.
*/
void freeBinaryTree(BinaryTree *out);

//! Create a #BinaryTreeNode and insert it in the #BinaryTree O(log(n))
/*!
  \param[out] out Pointer to #LinkedList object.
  \param[in] key Value for key of new #LinkedListNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #LinkedListNode inserted.
*/
BinaryTreeNode *insertBinaryTree(BinaryTree *out, int key, void *value);

//! Search for a node in the #BinaryTree given a key with complexity O(log(n))
/*!
  When no #BinaryTreeNode with this key is present, then return NULL

  \param[in] out Pointer to #BinaryTree object.
  \param[in] key Value for key of node to search
  \return A #BinaryTreeNode pointer to the node or NULL.
*/
BinaryTreeNode *getKeyBinaryTree(BinaryTree *out, int key);

//! Remove #BinaryTreeNode from #BinaryTree given a key O(n)
/*!
  Remove the #BinaryTreeNode node with a given key if exists

  \param[inout] out Pointer to #BinaryTree object.
  \param[in] key Value for key of node to remove
  \return 1 when a #BinaryTreeNode was removed or 0 when no such node was found.
*/
int popKeyBinaryTree(BinaryTree *out, int key);

//! Apply a function in Deep Search First (DSF) order
/*!
  The function uses the recursive implementation of dfs to run the tree in order.
  This is equivalent to 

  \param[inout] out Pointer to #BinaryTree object.
  \param[in] func Function to apply on every node.
  \param[inout] argument to pass to the function.
 */
void dsfBinaryTree(
	BinaryTree *inout,
	void (*func)(struct BinaryTreeNode *, void *),
	void *arg
);

//!@}

// Hash Table =================================================================

/*!
  \defgroup hash Simple Hash table using mod key function
  \brief This is a simple hash table based on the mod operation.

  It uses a double linked list as an underlying container to reduce insertion
  and deletion costs.
  @{
*/

//! Hash table node type
/*!
  This is like a typedef for DoubleLinkedListNode.
*/
typedef DoubleLinkedListNode HashTableNode;

//! Hash table container
/*!
  This is the simple container for #HashTable nodes.
*/
typedef struct HashTable {
	size_t entries;
	size_t N;

	// This is the array for the hash table.
	DoubleLinkedList *table;
} HashTable;

//! Constructor for #HashTable container
/*!
  \param[out] out Pointer to #HashTable object to construct.
  \param[in] N Number of hash entries in the hash table array.
*/
void allocInitHashTable(HashTable *out, size_t N);

//! Destructor for #HashTable container
/*!
  \param[out] out Pointer to #HashTable object to free.
*/
void freeHashTable(HashTable *out);

//! Create a #HashTableNode into the #HashTable O(1)
/*!
  \param[out] out Pointer to #HashTable object.
  \param[in] key Value for key of new #HashTableNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #HashTableNode inserted.
*/
HashTableNode *insertKeyHashTable(HashTable *out, int key, void *value);

//! Search for a node in the #HashTable given a key with complexity O(1 + n/m)
/*!
  When no #HashTableNode with this key is present, then return NULL

  \param[in] out Pointer to #HashTable object.
  \param[in] key Value for key of node to search
  \return A #HashTableNode pointer to the node or NULL.
*/
HashTableNode *getKeyHashTable(HashTable *out, int key);

//! Remove #HashTableNode from #HashTable given a key O(1+m/n)
/*!
  Remove a the first #HashTableNode with a given key if exists

  \param[inout] out Pointer to #HashTable object.
  \param[in] key Value for key of node to remove
  \return 1 when a #HashTableNode was removed or 0 when no such node was found.
*/
int popKeyHashTable(HashTable *out, int key);

//!@}

// LRU Table =================================================================

/*!
  \defgroup lrutable Simple Least Recently Used Hash table using mod key function
  \brief This is a hash table with a cache for node accesses.

  It uses a double linked list as an underlying container to reduce insertion
  and deletion costs. On the other hand there is also another underlying linked
  list which is modified on every access to promote and track the last accessed
  nodes. This method ensures that the head of the list is always the least
  recently used one,

  On the other hand there is also a limit for the number of elements the
  lruTable can hold. When that number is reached, every new insertion removes
  the Least Recently Used one. The code also implements some optimizations to
  avoid calling free-malloc in that case.
  @{
*/

//! LRU Hash Table node type
/*!

  This is like a #lruTableNode but includes two extra fields lruTableNode#left
  and lruTableNode#right which are the double linked list connections in the
  access cache.
*/
typedef struct lruTableNode {
	HashTableNode;               /*!< Parent class as first element. */

	// Extend with the double linked list nodes
	struct lruTableNode *left;  /*!< Pointer to the immediate left element in use cache. */
	struct lruTableNode *right; /*!< Pointer to the immediate right element in use cache. */
} lruTableNode;


//! LRU Hash Table container
/*!
  This is the container for #lruTable nodes. This is very similar to #HashTable
  in complexity and functionalities, but contains the lruTable#maxEntries unlike
  a normal #HashTable.
*/
typedef struct lruTable {
	struct HashTable;

	// Hash table with limited number of entries.
	size_t maxEntries;          /*!< Maximum number of entries that the lruTable can hold. */

	// Access list cache. needs two pointers to the first and last element.
	struct lruTableNode *accesList;   /*!< Pointer to the Least Recently Used access element. */
	struct lruTableNode *lastAccess;  /*!< Pointer to the Most Recently Used element. */
} lruTable;

//! Constructor for #lruTable container
/*!
  \param[out] out Pointer to #HashTable object to construct.
  \param[in] N Number of hash entries in the hash table array. This is also the
  max number of entries the #lruTable can hold before removing the older ones.
*/
void allocInitlruTable(lruTable *out, size_t N);

//! Destructor for #lruTable container
/*!
  \param[out] out Pointer to #lruTable object to free. This also releases all
  the elements contained
*/
void freelruTable(lruTable *out);

//! Create a #lruTableNode into the #lruTable given a key and value O(1)
/*!
  Inserting an element counts as an access, so the last inserted element is also
  the last accessed one. When the #lruTable already has lruTable#maxEntries
  elements this operation also removes the Least Recent Used node before
  inserting the new one.
  \param[out] out Pointer to #lruTable object.
  \param[in] key Value for key of new #lruTableNode
  \param[in] value Pointer object associated with the key (node content).
  \return A pointer to the new #lruTableNode inserted.
*/
lruTableNode *insertKeylruTable(lruTable *out, int key, void *value);

//! Search for a node in the #lruTable given a key with complexity O(1 + n/m)
/*!
  When no #lruTableNode with this key is present, then return NULL. This
  function registers all accesses to existing #lruTableNode into the access
  cache (implemented as a double linked list).

  \param[in] out Pointer to #lruTable object.
  \param[in] key Value for key of node to search
  \return A #lruTableNode pointer to the node or NULL.
*/
lruTableNode *getKeylruTable(lruTable *out, int key);

//!@}
#endif // C_CONTAINER_H
