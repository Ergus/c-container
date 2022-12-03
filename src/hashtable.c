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

// List Node ===================================================================

inline static size_t _hashFunction(HashTable *in, size_t key)
{
	return key % in->N;
}

void allocInitHashTable(HashTable *out, size_t N)
{
	out->entries = 0;
	out->N = N;

	out->table = malloc(N *sizeof(struct HashTable));
}

void freeHashTable(HashTable *out)
{
	for (size_t i = 0; i < out->N; ++i) {
		freeLinkedList(&out->table[i]);
	}

	free(out->table);
	out->entries = 0;
}

HashTableNode *insertHashTable(HashTable *out, int key, void *value)
{
	const size_t hash = _hashFunction(out, key);
	assert(hash < out->N);

	LinkedList *hashEntry = &out->table[hash];
	HashTableNode *node = getKeyLinkedList(hashEntry, key);

	if (node == NULL) {
		out->entries++;
		node = insertLinkedList(hashEntry, key, value);
	} else {
		free(node->value);
		node->value = value;
	}

	return node;
}

HashTableNode *getKeyHashTable(HashTable *out, int key)
{
	const size_t hash = _hashFunction(out, key);
	assert(hash < out->N);

	return getKeyLinkedList(&out->table[hash], key);
}
