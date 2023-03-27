#include "multiset.h"

multiset_t* ms_create(unsigned int max, unsigned int (*hash_function)(void*),
		      int (*compare_function)(void*, void*))
{
	return ht_create(max, hash_function, compare_function);
}

void ms_put(multiset_t *ms, void *key, unsigned int key_size)
{
	int count = 1;
	int *pcount = ht_get(ms, key);

	if(pcount)
		count = *pcount + 1;

	ht_put(ms, key, key_size, &count, sizeof(count));
}

int ms_get(multiset_t *ms, void *key)
{
	int *pcount = ht_get(ms, key);

	if(pcount)
		return *pcount;

	return 0;
}

int ms_remove(multiset_t *ms, void *key, unsigned int key_size)
{
	int count;
	int *pcount = ht_get(ms, key);

	if(!pcount)
		return -1;

	count = *pcount - 1;

	if(count == 0)
		ht_remove_entry(ms, key);
	else
		ht_put(ms, key, key_size, &count, sizeof(count));

	return count;
}

int ms_complete_remove(multiset_t *ms, void *key)
{
	if(ht_get(ms, key)) {
		ht_remove_entry(ms, key);
		return 1;
	}
	return 0;
}

void ms_free(multiset_t *ms)
{
	ht_free(ms);
}
