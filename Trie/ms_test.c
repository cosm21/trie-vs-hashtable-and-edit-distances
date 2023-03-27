#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Hashtable.h"
#include "LinkedList.h"
#include "multiset.h"

#define WORD_LEN 255
#define BUCKET_SIZE 524288

/*
 * Functie care calculeaza diferenta de timp dintre doua momente
 * Rezultatul e in nanosecunde
 */
long time_nsec_diff(struct timespec *ts1, struct timespec *ts2)
{
        if (!ts1 || !ts2)
                return 0;

        return (ts2->tv_sec - ts1->tv_sec) * 1e9 +
	       (ts2->tv_nsec - ts1->tv_nsec);
}

/*
 * Functie care compara doi pointeri dubli la siruri de caractere
 * E nevoie de aceasta functie pentru a sorta elementele unui
 * hashtable.
 */
int cmp(const void* ptr1, const void *ptr2)
{
	char *str1, *str2;

	if(!ptr1 || !ptr2)
		return 0;

	str1 = *((char**)ptr1);
	str2 = *((char**)ptr2);

	return strcmp(str1, str2);
}

/*
 * Afiseaza in ordine elemenetele unui hashtable care contine pe post
 * de cheie doar cuvinte
 */
void ht_print(hashtable_t *ht, FILE *fout)
{
	struct info *tmp;
	ll_node_t *node;
	linked_list_t *list;

	if(!ht)
		return;

	// Pentru a sorta hashtable-ul se creaza o lista inlantuita
	// noua care va contine toate nodurile acelui hashtable
	list = ll_create(sizeof(char*));

	for(int i = 0; i < ht->hmax; ++i) {
		for(node = ht->buckets[i]->head; node; node = node->next) {
			tmp = node->data;
			// Fiecare nod trebuie sa stocheze in lista un pointer
			// la un sir de caractere, deoarece fiecare sir
			// poate avea o lungime diferita, lista inlantuita
			// nu permite acest lucru
			ll_add_nth_node(list, 0, &tmp->key);
		}
	}

	ll_sort(list, cmp);

	for(node = list->head; node; node = node->next)
		fprintf(fout, "Print: \"%s\".\n", *((char**)node->data));

	ll_free(&list);
}

int main()
{
	multiset_t *ms;
	FILE *fin, *fout;
	char op, word[WORD_LEN + 1];
	int count, ret;

	struct timespec tic, toc;
	long insert_nsec = 0, delete_nsec = 0, print_nsec = 0, lookup_nsec = 0;

	ms = ms_create(BUCKET_SIZE, hash_function_string, compare_function_strings);
	if(!ms) {
		printf("Failed to allocate memory for hashtable!\n");
		return 0;
	}
	fin = fopen("test.in", "r");
	if(!fin) {
		printf("Failed to open the input file!\n");
		ms_free(ms);
		return 0;
	}
	fout = fopen("test.out", "w");
	if(!fout) {
		printf("Failed to open output file!\n");
		ms_free(ms);
		fclose(fin);
		return 0;
	}

	for(;;) {
                fscanf(fin, " %c", &op);
                if (op == 'E')
                        break;
                switch (op) {
                case 'I':
			fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			ms_put(ms, word, strlen(word) + 1);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			insert_nsec += time_nsec_diff(&tic, &toc);

                        fprintf(fout, "Insert: \"%s\".\n", word);
                        break;
                case 'L':
                        fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			count = ms_get(ms, word);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			lookup_nsec += time_nsec_diff(&tic, &toc);

			if(!count) {
				fprintf(fout, "Lookup: \"%s\" not found!\n", word);
				break;
			}
			fprintf(fout, "Lookup: \"%s\" found.\n", word);

                        break;
                case 'P':
			clock_gettime(CLOCK_MONOTONIC, &tic);
			ht_print(ms, fout);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			print_nsec += time_nsec_diff(&tic, &toc);

			break;
                case 'D':
                        fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			count = ms_complete_remove(ms, word);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			delete_nsec += time_nsec_diff(&tic, &toc);

			if(!count) {
				fprintf(fout, "Delete: \"%s\" not found!\n", word);
				break;
			}
			fprintf(fout, "Delete: \"%s\" deleted.\n", word);

                        break;
                default:
                        printf("Op not implemented!\n");
                        break;
                }
        }

	// Aici se fac afisarile timpilor, au fost scoase ca sa se poata
	// vedea evaluarea programului de verificare
	/*
	printf("Times:\n");
        printf("Insert: %g msec\n", ((double)insert_nsec) / 1000000);
        printf("Lookup: %g msec\n", ((double)lookup_nsec) / 1000000);
        printf("Delete: %g msec\n", ((double)delete_nsec) / 1000000);
        printf("Print: %g msec\n", ((double)print_nsec) / 1000000);
        printf("TOTAL: %g msec\n", ((double)(insert_nsec + lookup_nsec + delete_nsec)) / 1000000);
	*/

	fclose(fin);
	fclose(fout);
	ms_free(ms);
	return 0;
}
