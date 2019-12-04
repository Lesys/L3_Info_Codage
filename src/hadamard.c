#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <matrice.h>
#include <hadamard.h>

// Création de la matrice de hadamard de rang n
//
// Renvoie 0 si erreur, 1 si succès
int hadamard_matrice(int n, matrice_t * matrice) {
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		matrice->tab = malloc(sizeof(char));
		if (matrice->tab == NULL) {
			fprintf(stderr, "Problème mémoire\n");
			return 0;
		}
		matrice->tab[0] = 1;
		matrice->nb_lignes = 1;
		matrice->nb_colonnes = 1;
		return 1;
	}
	else {
		matrice_t matrice_prec;
		// Création matrice précédente
		hadamard_matrice(n-1, &matrice_prec);
		// Initialisations et allocation pour notre nouvelle matrice
		matrice->nb_lignes = matrice_prec.nb_lignes * 2;
		matrice->nb_colonnes = matrice_prec.nb_colonnes * 2;
		matrice->tab = malloc(pow(matrice->nb_lignes, 2) * sizeof(char));
		// Mise en place des valeurs
		for (int i = 0; i < matrice->nb_lignes; i++) {
			for (int j = 0; j < matrice->nb_colonnes; j++) {
				if (i >= matrice_prec.nb_lignes && j >= matrice_prec.nb_colonnes) {
					VAL((*matrice), i, j) = -VAL(matrice_prec, i % matrice_prec.nb_colonnes, j % matrice_prec.nb_colonnes);
				}
				else {
					VAL((*matrice), i, j) = VAL(matrice_prec, i % matrice_prec.nb_colonnes, j % matrice_prec.nb_colonnes);
				}
			}
		}
		return 1;
	}
}
