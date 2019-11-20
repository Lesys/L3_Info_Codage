#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hadamard.h"

void afficher_matrice(matrice_t matrice) {
	for(int i = 0; i < matrice.largeur; i++) {
		for (int j = 0; j < matrice.largeur; j++) {
			printf("%3d ", matrice.tab[i*matrice.largeur + j]);
		}
		printf("\n\n");
	}
}


int hadamard_matrice(int n, matrice_t * matrice) {
	if (n < 0) {
		return 0;
	}
	if (n == 0) {
		matrice->tab = malloc(sizeof(char));
		matrice->tab[0] = 1;
		matrice->largeur = 1;
		return 1;
	}
	else {
		matrice_t matrice_prec;
		hadamard_matrice(n-1, &matrice_prec);
		matrice->largeur = matrice_prec.largeur * 2;
		matrice->tab = malloc(pow(matrice->largeur, 2) * sizeof(char));
		for (int i = 0; i < matrice->largeur; i++) {
			for (int j = 0; j < matrice->largeur; j++) {
				if (i >= matrice_prec.largeur && j >= matrice_prec.largeur) {
					matrice->tab[i*matrice->largeur + j] = -matrice_prec.tab[((i % matrice_prec.largeur) * matrice_prec.largeur) + (j % matrice_prec.largeur)];
				}
				else {
					matrice->tab[i*matrice->largeur + j] = matrice_prec.tab[((i % matrice_prec.largeur) * matrice_prec.largeur) + (j % matrice_prec.largeur)];
				}
			}
		}
		return 1;
	}
}
