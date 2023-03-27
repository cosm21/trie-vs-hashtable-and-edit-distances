#ifndef TRIE_H_
#define TRIE_H_

#include <stdio.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 255

/*
 * Nodul contine valoarea asociata unui cuvant, 0 este
 * pentru radacina, iar orice alta valoare mai mare de
 * atat este semnifica ca acel nod reprezinta sfarsitul
 * unui cuvant
 */
struct trie_node_t {
	int value;
	struct trie_node_t **children;
};

struct trie_t {
	struct trie_node_t *root;
};

struct trie_node_t* trie_create_node();
struct trie_t* trie_create();

void trie_node_free(struct trie_node_t *node);
void trie_free(struct trie_t *trie);

void trie_insert(struct trie_t *trie, char *word, int value);

int trie_lookup(struct trie_t *trie, char *word);

int trie_delete(struct trie_t *trie, char *word);

void trie_print(struct trie_t *trie, FILE *fout);
#endif
