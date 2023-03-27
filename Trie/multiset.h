#ifndef __MULTISET_H_
#define __MULTISET_H_

#include "Hashtable.h"

typedef hashtable_t multiset_t;

multiset_t* ms_create(unsigned int max, unsigned int (*hash_function)(void*),
			    int (*compare_function)(void*, void*));
void ms_put(multiset_t *ms, void *key, unsigned int key_size);
int ms_get(multiset_t *ms, void *key);

int ms_remove(multiset_t *ms, void *key, unsigned int key_size);
int ms_complete_remove(multiset_t *ms, void *key);

void ms_free(multiset_t *ms);

#endif
