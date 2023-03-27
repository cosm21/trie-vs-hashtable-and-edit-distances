#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "distance.h"

#define MAX_WORD_LEN 255

/*
 * Calculeaza diferenta in nanosecunde dintre doua momente de timp
 */
long time_nsec_diff(struct timespec *ts1, struct timespec *ts2)
{
        if (!ts1 || !ts2)
                return 0;

        return (ts2->tv_sec - ts1->tv_sec) * 1e9 +
	       (ts2->tv_nsec - ts1->tv_nsec);
}

int main()
{
	char word1[MAX_WORD_LEN + 1], word2[MAX_WORD_LEN + 1];
	struct timespec tic, toc;
	long time_lvs = 0, time_dmlvs = 0;
	int n, dist_lvs, dist_dmlvs, len1, len2;
	int limit;
	FILE *fin, *fout;

	fin = fopen("test.in", "r");
	if(!fin) {
		printf("Failed to open input file!\n");
		return 0;
	}
	fout = fopen("test.out", "w");
	if(!fout) {
		printf("Failed to open output file!\n");
		fclose(fin);
		return 0;
	}

	fscanf(fin, "%d%d", &n, &limit);

	for(int i = 0; i < n; ++i) {
		fscanf(fin, "%s%s", word1, word2);
		len1 = strlen(word1);
		len2 = strlen(word2);

		clock_gettime(CLOCK_MONOTONIC, &tic);
		dist_lvs = uk_lvs(word1, word2, len1, len2, limit);
		clock_gettime(CLOCK_MONOTONIC, &toc);

		time_lvs += time_nsec_diff(&tic, &toc);

		clock_gettime(CLOCK_MONOTONIC, &tic);
		dist_dmlvs = uk_dmlvs(word1, word2, len1, len2, limit);
		clock_gettime(CLOCK_MONOTONIC, &toc);

		time_dmlvs += time_nsec_diff(&tic, &toc);

		fprintf(fout, "%d %d\n", dist_lvs, dist_dmlvs);
	}

	/*
	printf("LVS: %g msec\n", ((double)time_lvs) / 1000000);
	printf("DMLVS: %g msec\n", ((double)time_dmlvs) / 1000000);
	*/

	fclose(fin);
	fclose(fout);
	return 0;
}
