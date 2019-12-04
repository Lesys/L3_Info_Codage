#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/binaire_formate.h"

#define set_bit(v, p) v |= 1 << p;

bf_t transformer_donnee_bit(void * donnee, int taille) {
	bf_t bits = malloc(taille * 8 + 1);
	char * donnee_char = donnee;

	int i, j;
	for (i = 0; i < taille; i++) {
		for (j = 7; j >= 0; j--) {
			bits[i * 8 + (7 - j)] = (donnee_char[i] & (1 << j) ? '1' : '0');
		}
	}
	
	bits[taille * 8] = '\0';

	return bits;
}

void * transformer_bit_donnee(bf_t bin) {
	int taille = strlen(bin) / 8;
	char * donnee_char = calloc(sizeof(char), taille);

	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < 8; j++ ) {
			if (bin[(i * 8) + j] == '1') {
				set_bit(donnee_char[i], -1 * (j - 7));
			}
		}
	}

	return donnee_char;
}