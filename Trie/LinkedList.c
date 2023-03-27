#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t* ll_create(unsigned int data_size)
{
	linked_list_t* ll;

	ll = malloc(sizeof(*ll));
	DIE(ll == NULL, "linked_list malloc");

	ll->head = NULL;
	ll->data_size = data_size;
	ll->size = 0;

	return ll;
}

void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *prev, *curr;
	ll_node_t* new_node;

	if (list == NULL) {
		return;
	}

	if (n > list->size) {
		n = list->size;
	} else if (n < 0) {
		return;
	}

	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}

	new_node = malloc(sizeof(*new_node));
	DIE(new_node == NULL, "new_node malloc");
	new_node->data = malloc(list->data_size);
	DIE(new_node->data == NULL, "new_node->data malloc");
	memcpy(new_node->data, new_data, list->data_size);

	new_node->next = curr;
	if (prev == NULL) {
		list->head = new_node;
	} else {
		prev->next = new_node;
	}

	list->size++;
}

ll_node_t* ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *prev, *curr;

	if (list == NULL) {
		return NULL;
	}

	if (list->head == NULL) {
		return NULL;
	}

	if (n > list->size - 1) {
		n = list->size - 1;
	}

	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}

	if (prev == NULL) {
		list->head = curr->next;
	} else {
		prev->next = curr->next;
	}

	list->size--;

	return curr;
}

unsigned int ll_get_size(linked_list_t* list)
{
	if (list == NULL) {
		return -1;
	}

	return list->size;
}

void ll_free(linked_list_t** pp_list)
{
	ll_node_t* currNode;

	if (pp_list == NULL || *pp_list == NULL) {
		return;
	}

	while (ll_get_size(*pp_list) > 0) {
		currNode = ll_remove_nth_node(*pp_list, 0);
		free(currNode->data);
		free(currNode);
	}

	free(*pp_list);
	*pp_list = NULL;
}

void ll_print_int(linked_list_t* list)
{
	ll_node_t* curr;

	if (list == NULL) {
		return;
	}

	curr = list->head;
	while (curr != NULL) {
		printf("%d ", *((int*)curr->data));
		curr = curr->next;
	}

	printf("\n");
}

void ll_print_string(linked_list_t* list)
{
	ll_node_t* curr;

	if (list == NULL) {
		return;
	}

	curr = list->head;
	while (curr != NULL) {
		printf("%s ", (char*)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/*
 * Functie care imbina doua liste date sub forma de noduri.
 * Aceasta functie este o liniarizare a variantei oferite
 * de geeksforgeeks pentru aceasi operatie:
 * https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 */
static ll_node_t* ll_merge_lists(ll_node_t *node1, ll_node_t *node2,
				int (*cmp)(const void*, const void*))
{
	ll_node_t *node = NULL, *head;
	ll_node_t *next1, *next2;

	if(!node1)
		return node2;
	if(!node2)
		return node1;

	for(;;) {
		if(!node1) {
			node->next = node2;
			break;
		}
		if(!node2) {
			node->next = node1;
			break;
		}

		next1 = node1->next;
		next2 = node2->next;

		if(cmp(node1->data, node2->data) <= 0) {
			if(!node) {
				node = node1;
				node1 = next1;
				head = node;
				continue;
			}

			node->next = node1;
			node = node->next;
			node1 = next1;
		} else {
			if(!node) {
				node = node2;
				node2 = next2;
				head = node;
				continue;
			}

			node->next = node2;
			node = node->next;
			node2 = next2;
		}
	}

	return head;
}

/*
 * Imparte o lista in doua. Luata de pe geeksforgeeks:
 * https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 */
static void ll_split_half(ll_node_t *node, ll_node_t **front, ll_node_t **back)
{
	ll_node_t *node1, *node2;

	if(!node)
		return;

	node1 = node;
	node2 = node->next;

	while(node2) {
		node2 = node2->next;
		if(node2) {
			node1 = node1->next;
			node2 = node2->next;
		}
	}

	*front = node;
	*back = node1->next;
	node1->next = NULL;
}

/*
 * Merge sort pe doua liste. Luata de pe geeksforgeeks:
 * https://www.geeksforgeeks.org/merge-sort-for-linked-list/
 */
static void ll_merge_sort(ll_node_t **head,
			  int (*cmp)(const void*, const void*))
{
	ll_node_t *node, *front, *back;

	if(!*head)
		return;

	node = *head;

	if(!node || !node->next)
		return;

	ll_split_half(node, &front, &back);

	ll_merge_sort(&front, cmp);
	ll_merge_sort(&back, cmp);

	*head = ll_merge_lists(front, back, cmp);
}

/*
 * Apeleaza functia de merge sort
 */
void ll_sort(linked_list_t *list, int (*cmp)(const void*, const void*))
{
	if(!list)
		return;

	ll_merge_sort(&list->head, cmp);
}
