#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Functie care aloca memorie pentru nodul unui trie
 */
struct trie_node_t* trie_create_node()
{
	struct trie_node_t *node = malloc(sizeof(*node));
	if (!node)
		return NULL;

	node->children = malloc(sizeof(*node->children) * ALPHABET_SIZE);
	if (!node->children) {
		free(node);
		return NULL;
	}

	// Initializez toti copii cu NULL, aceastia vor fi alocati
	// cand e nevoie
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		node->children[i] = NULL;

	node->value = 0;

	return node;
}

/*
 * Aloca memorie pentru structura de trie
 */
struct trie_t* trie_create()
{
	struct trie_t *trie = malloc(sizeof(*trie));
	if (!trie)
		return NULL;

	trie->root = trie_create_node();
	if (!trie->root) {
		free(trie);
		return NULL;
	}

	return trie;
}

/*
 * Elibereaza memoria ocupata de un nod
 */
void trie_node_free(struct trie_node_t *node)
{
	if(!node)
		return;
	free(node->children);
	free(node);
}

/*
 * Functie recursiva care elibereaza intregul trie
 */
static void _trie_free(struct trie_node_t *node)
{
	// Parcurg intai toti copii nodului
	for(int i = 0; i < ALPHABET_SIZE; ++i)
		if(node->children[i])
			_trie_free(node->children[i]);
	// Si apoi eliberez nodul in sine
	trie_node_free(node);
}

/*
 * Partea nerecursiva a functiei de eliberarea a trie-ului
 */
void trie_free(struct trie_t *trie)
{
	_trie_free(trie->root);
	free(trie);
	return;
}

/*
 * Insereaza un cuvant in trie
 */
void trie_insert(struct trie_t *trie, char *word, int value)
{
	int pos = 0, len;
	struct trie_node_t *node;

	if (!trie || !word || value <= 0)
		return;

	len = strlen(word);
	if (len <= 0)
		return;
	node = trie->root;

	// Parcurg fiecare caracter din cuvantul de intrare
	// in tandem cu arborele
	for(pos = 0; pos < len; ++pos) {
		// Daca nodul urmator nu exista atunci il creez
		if(!node->children[word[pos] - 'a']) {
			node->children[word[pos] - 'a'] = trie_create_node();
			if (!node->children[word[pos] - 'a'])
				return;
			// Daca nu am ajuns la final, atunci nodul nou
			// creat nu este considerat un cuvant
			node->children[word[pos] - 'a']->value = -1;
		}

		node = node->children[word[pos] - 'a'];
	}

	// Dupa ce s-a facut parcurgere, ultimul nod este sfarsitul
	// cuvantului si va primi valoarea asociata
	node->value = value;
}

/*
 * Cauta un cuvant in trie
 */
int trie_lookup(struct trie_t *trie, char *word)
{
	int pos, len;
	struct trie_node_t *node;

	if(!trie || !word)
		return 0;

	node = trie->root;
	for(pos = 0; word[pos]; ++pos) {
		// Daca nodul corespunzator acelei litere nu exista
		// atunci e clar ca nici restul cuvantului nu poate
		// exista in trie, deci pot sa ma opresc
		if(!node->children[word[pos] - 'a'])
			return 0;

		node = node->children[word[pos] - 'a'];
	}

	// Daca nu s-a terminat functia mai devreme, atunci
	// inseamna ca literele cuvantului cautat sunt prezente
	// in trie, dar asta nu inseamna neaparat ca si
	// cuvantul in sine face parte din trie
	if(node->value > 0)
		return node->value;
	else
		return 0;
}

/*
 * Verifica daca un nod e o frunza
 */
static int _trie_node_is_leaf(struct trie_node_t *root)
{
	for(int i = 0; i < ALPHABET_SIZE; ++i)
		if(root->children[i])
			return 0;
	return 1;
}

/*
 * Functia de stergere a unui cuvant din trie
 */
static int _trie_delete(struct trie_node_t *node, char *word,
			int length, int index)
{
	int ret;
	struct trie_node_t *child_node;

	if(!node)
		return 0;

	child_node = NULL;
	if(word[index] - 'a' >= 0 && node->children[word[index] - 'a'])
		child_node = node->children[word[index] - 'a'];

	// Tratez cazul in care s-a ajuns la sfarsitul cuvantului, caz
	// in care ar trebui sa ma opresc din parcurs arborele si sa
	// incep eliberarea din memorie
	if(index == length - 1 && child_node && child_node->value > 0) {
		child_node->value = -1;
		if(_trie_node_is_leaf(child_node)) {
			trie_node_free(child_node);
			node->children[word[index] - 'a'] = NULL;
		}
		return 1;
	}

	// Daca exista copilul corespunzator literei atunci il parcurg
	if(child_node)
		ret = _trie_delete(child_node, word, length, index + 1);
	else
		return 0;

	// Aceasta parte este rulata odata ce s-a ajuns la sfarsitul
	// cuvantului si se iese din apelurile de functie
	// Daca nodul la care se afla functia este o frunza si nu
	// este un cuvant atunci acesta poate fi eliberat
	if(_trie_node_is_leaf(child_node) && child_node->value < 0) {
		trie_node_free(child_node);
		node->children[word[index] - 'a'] = NULL;
	}

	// Functia intoarce mai departe 1 sau 0, daca cuvantul era
	// in trie sau nu
	return ret;
}

/*
 * Partea nerecursiva a stergerii din trie
 */
int trie_delete(struct trie_t *trie, char *word)
{
	int index = 0, length;
	struct trie_node_t *node;

	if(!trie || !word)
		return -1;

	length = strlen(word);
	if(length <= 0)
		return -1;

	return _trie_delete(trie->root, word, length, 0);
}

/*
 * Afiseaza recursiv toate cuvintele din trie
 */
static void _trie_print(struct trie_node_t *node, char *word,
			int pos, FILE *fout)
{
	// Daca ce a fost parcurs pana aici este un cuvant, atunci
	// se afiseaza
	if(node->value > 0)
		fprintf(fout, "Print: \"%s\".\n", word);


	for(int i = 0; i < ALPHABET_SIZE; ++i) {
		if(node->children[i]) {
			// Pe masura ce parcurg arborele, tot adaug
			// la sfarsitul sirului de caractere litera
			// care ii corespunde acelui nod
			word[pos] = 'a' + i;
			word[pos + 1] = '\0';
			_trie_print(node->children[i], word, pos + 1, fout);
			// Pe masura ce incep sa ma intorc din apeluri, adica
			// sa revin la un nod anterior, scot litera acelui
			// nod din sir
			word[pos] = '\0';
		}
	}
}

/*
 * Partea nerecursiva a afisarii
 */
void trie_print(struct trie_t *trie, FILE *fout)
{
	char word[MAX_WORD_LEN + 1] = "";
	if(!trie)
		return;
	_trie_print(trie->root, word, 0, fout);
}
