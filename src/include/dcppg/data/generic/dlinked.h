#ifndef DCPPG_DATA_GENERIC_DLINKED_H
#define DCPPG_DATA_GENERIC_DLINKED_H

#include <stdlib.h>

typedef struct DLinkedNode {
	void (*destructor)(void *);
	size_t index;
	size_t prev_index;
	size_t next_index;
	struct DLinkedNode * prev;
	struct DLinkedNode * next;
	struct DLinked     * master;
	void * data;
} DLinkedNode;

typedef struct DLinked {
	void (*default_destructor)(void *);
	size_t used;
	size_t power;
	DLinkedNode * first;
	DLinkedNode * last;
	size_t first_index;
	size_t last_index;
	DLinkedNode * nodes;
	DLinkedNode ** nodemap;
} DLinked;

typedef struct {
	void (*init)(DLinked *, void(*)(void*), char);
	void (*deinit)(DLinked *);

	DLinkedNode * (*push_back)(DLinked *, void *, void (*)(void*));
	DLinkedNode * (*push_back_copy)(DLinked *, void const*, size_t);
	DLinkedNode * (*push_back_string)(DLinked *, char const*);

	void (*delete_node)(DLinkedNode *);

	void (*sort)(DLinked *, size_t, size_t, char (*)(void *, void*));
} DLinkedSymbols;
#endif
