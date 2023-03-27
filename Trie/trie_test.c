#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORD_LEN 255

long time_nsec_diff(struct timespec *ts1, struct timespec *ts2)
{
	if(!ts1 || !ts2)
		return 0;

	return (ts2->tv_sec - ts1->tv_sec) * 1e9 + (ts2->tv_nsec - ts1->tv_nsec);
}

int main()
{
	struct trie_t *trie = trie_create();
	FILE *fin, *fout;
	int value;
	char word[WORD_LEN + 1];
	char op;

	// Pentru masurarea timpilor
	struct timespec tic, toc;
	long insert_nsec = 0, delete_nsec = 0, print_nsec = 0, lookup_nsec = 0;

	if(!trie) {
		printf("Failed to allocate memory for trie!\n");
		return 0;
	}
	fin = fopen("test.in", "r");
	if (!fin) {
		printf("Failed to open input file!\n");
		trie_free(trie);
		return 0;
	}
	fout = fopen("test.out", "w");
	if(!fout) {
		printf("Failed to open output file!\n");
		trie_free(trie);
		fclose(fin);
		return 0;
	}

	for(;;) {
		fscanf(fin, " %c", &op);
		if (op == 'E')
			break;
		switch(op) {
		case 'I':
			fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			trie_insert(trie, word, 1);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			insert_nsec += time_nsec_diff(&tic, &toc);

			fprintf(fout, "Insert: \"%s\".\n", word);
			break;
		case 'L':
			fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			value = trie_lookup(trie, word);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			lookup_nsec += time_nsec_diff(&tic, &toc);

			if(!value)
				fprintf(fout, "Lookup: \"%s\" not found!\n", word);
			else
				fprintf(fout, "Lookup: \"%s\" found.\n", word);
			break;
		case 'P':
			clock_gettime(CLOCK_MONOTONIC, &tic);
			trie_print(trie, fout);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			print_nsec += time_nsec_diff(&tic, &toc);

			break;
		case 'D':
			fscanf(fin, "%255s", word);

			clock_gettime(CLOCK_MONOTONIC, &tic);
			value = trie_delete(trie, word);
			clock_gettime(CLOCK_MONOTONIC, &toc);

			delete_nsec += time_nsec_diff(&tic, &toc);

			if(!value)
				fprintf(fout, "Delete: \"%s\" not found!\n", word);
			else
				fprintf(fout, "Delete: \"%s\" deleted.\n", word);
			break;
		default:
			printf("Op not implemented!\n");
			break;
		}
	}

	// Aici se fac afisarile timpilor, au fost scoase ca sa se poata
	// vedea evaluarea scripturilor de testare
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
	trie_free(trie);
	return 0;
}
