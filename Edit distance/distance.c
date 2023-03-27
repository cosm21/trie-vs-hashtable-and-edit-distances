#include "distance.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

/*
 * Algoritmul Wagner-Fischer pentru distanta Levenshtein
 */
int lvs(char *a, char *b, int len_a, int len_b)
{
	if(!a || !b)
		return -1;

	// Tratez niste cazuri simple
	if(!len_a && len_b)
		return len_b;

	if(len_a && !len_b)
		return len_a;

	int matrix[len_a + 1][len_b + 1];

	for(int i = 0; i < len_a + 1; ++i)
		matrix[i][0] = i;
	for(int i = 0; i < len_b + 1; ++i)
		matrix[0][i] = i;

	for(int i = 1; i < len_a + 1; ++i) {
		for(int j = 1; j < len_b + 1; ++j) {
			// Se calculeaza minimul dintre o inserare, stergere sau schimbare
			// pe acea pozitie
			matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1),
					       matrix[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
		}
	}

	return matrix[len_a][len_b];
}

/*
 * Aceeasi implementare ca mai sus, doar ca are o modifcare prin care
 * se trateaza si transpozitiile
 */
int dmlvs(char *a, char *b, int len_a, int len_b)
{
	if(!a || !b)
		return -1;

	if(!len_a && len_b)
		return len_b;

	if(len_a && !len_b)
		return len_a;

	int matrix[len_a + 1][len_b + 1];

	for(int i = 0; i < len_a + 1; ++i)
		matrix[i][0] = i;
	for(int i = 0; i < len_b + 1; ++i)
		matrix[0][i] = i;

	for(int i = 1; i < len_a + 1; ++i) {
		for(int j = 1; j < len_b + 1; ++j) {
			matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1),
					       matrix[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
			// se mai verifica in plus daca operatia de interschimbare
			// are un cost mai mic
			if(i >= 2 && j >= 2 && (a[i - 1] == b[j - 2]) && (b[j - 1] == a[i - 2]))
				matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1);
		}
	}

	return matrix[len_a][len_b];
}

int abs(int a)
{
	if(a < 0)
		return -a;
	return a;
}

/*
 * Algoritmul imbunatatit al lui Ukkonen, asa cum este descris in publicatia:
 * https://www.sciencedirect.com/science/article/pii/S0019995885800462.
 *
 * Cu inspiratii in pseudocod de la: http://www.berghel.net/publications/asm/asm.php
 *
 * Descriere:
 * 
 * In loc sa se memoreze o matrice care pastreaza toate distantele posibile,
 * se va stoca o matrice pentru care indicii liniilor reprezinta
 * diagonale din matricea folosita in algoritmul simplu, iar indicii coloanelor
 * reprezinta distantele dintre sirurile de caractere.
 *
 * In matricea noua, numita f, pe pozitia f[k][p] se va gasi linia cea mai mare
 * din matricea veche, d, pt care pe diagonala k se mai gaseste distanta p. Liniile
 * si coloanele matricei f sunt indexate si negativ.
 *
 * Conform demonstratiilor facute de Ukkonen, acest mod de a stoca matricea
 * poate aduce imbunatatiri in ceea ce priveste timpul si spatiul.
 *
 * In aceasta noua matrice voi calcula coloana cu coloana elementele, pana
 * cand il gasesc pe p, distanta pentru care f[len_b - len_a][p] == len_a,
 * ceea ce semnifica ca, practic s-au parcurs complet sirurile de caractere
 * si ca in d[m][n] s-ar fi gasit distanta p.
 * 
 */
int uk_lvs(char *a, char *b, int len_a, int len_b, int limit)
{
	int k, p, r, ind_k, t;
	int max_len = max(len_a, len_b);
	int num_cols, num_rows;
	int zero_k, start, end;

	// Daca se da o limita, aceasta va fi considerata
	// pentru caculul matricei f
	if(limit != -1 && limit < max_len)
		max_len = limit;

	num_cols = max_len + 2;
	num_rows = 2 * max_len + 1;
	// In matricea f, liniile sunt indexate si negativ,
	// de aceea avem nevoie de o variabila care poate
	// trece de la indecsi negativi la indecsi pozitivi
	zero_k = num_rows / 2;

	int f[num_rows][num_cols];

	// Initializarea matricei f
	for(k = -zero_k; k < num_rows - zero_k; ++k) {
		for(p = -1; p < num_cols - 1; ++p) {
			if(p == abs(k) - 1) {
				if(k < 0)
					f[k + zero_k][p + 1] = -k - 1;
				else
					f[k + zero_k][p + 1] = -1;
			} else if (p < abs(k)) {
				f[k + zero_k][p + 1] = INT_MIN;
			}
		}
	}

	// Variabilele au aceeasi semnificatie ca in hartia lui Ukkonen
	p = -1;
	r = p - min(len_a, len_b);
	if(limit != -1)
		r = min(r, p - limit);
	do {
		p++;
		r++;

		if(r <= 0) {
			start = -p;
			end = p;
		} else {
			start = max(-len_a, -p);
			if(limit != -1)
				start = max(-limit, r);
			end = min(len_b, p);
			if(limit != -1)
				end = min(end, limit);
		}

		for(k = start; k <= end; ++k) {
			// Se va calcula maximul dintre
			// f[k][p - 1] + 1, f[k - 1][p - 1], f[k - 1][p - 1] + 1
			t = f[k + zero_k][p] + 1;

			if(k + zero_k - 1 >= 0 && f[k + zero_k - 1][p] > t)
				t = f[k + zero_k - 1][p];

			if(k + zero_k + 1 < num_rows && f[k + zero_k + 1][p] + 1 > t)
				t = f[k + zero_k + 1][p] + 1;

			while(t < len_a && t + k < len_b && a[t] == b[t + k])
				++t;

			f[k + zero_k][p + 1] = t;
		}

		if(limit != -1 && p > limit && limit < len_a)
			break;
	} while (f[len_b - len_a + zero_k][p] < len_a);

	return p - 1;
}

/*
 * O varianta propusa de Ukkonen, mai putin eficienta, dar posibil
 * mai rapida daca se da o limita pentru distanta
 */
int uk_dmlvs(char *a, char *b, int len_a, int len_b, int limit)
{
	// Daca nu se da o limita atunci algoritmul este identic
	if(limit == -1)
		return dmlvs(a, b, len_a, len_b);

	if(!a || !b)
		return -1;

	// Tratez niste situatii simple
	if(!len_a && len_b)
		return len_b;

	if(len_a && !len_b)
		return len_a;

	int matrix[len_a + 1][len_b + 1];

	for(int i = 0; i < len_a + 1; ++i)
		matrix[i][0] = i;
	for(int i = 0; i < len_b + 1; ++i)
		matrix[0][i] = i;

	for(int i = 1; i < len_a + 1; ++i) {
		for(int j = 1; j < len_b + 1; ++j) {
			// calculez doar acele valori care se afla pe diagonalele
			// impuse de algoritm
			if(abs(j - i) > limit)
				continue;

			matrix[i][j] = matrix[i - 1][j - 1] + (a[i - 1] != b[j - 1]);

			if(abs(j - i + 1) <= limit && matrix[i - 1][j] + 1 < matrix[i][j])
				matrix[i][j] = matrix[i - 1][j] + 1;

			if(abs(j - 1 - i) <= limit && matrix[i][j - 1] + 1 < matrix[i][j])
				matrix[i][j] = matrix[i][j - 1] + 1;

			if(i >= 2 && j >= 2 && (a[i - 1] == b[j - 2]) && (b[j - 1] == a[i - 2]))
                                matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1);
		}
	}

	return matrix[len_a][len_b];
}
