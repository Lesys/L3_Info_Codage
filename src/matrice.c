#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/matrice.h"

// Création d'une nouvelle matrice vide
//
// Retourne la matrice créée
matrice_t matrice_creer() {
  matrice_t matrice;
  matrice.nb_lignes = 0;
  matrice.nb_colonnes = 0;
  return matrice;
}

// Destruction d'une matrice
void matrice_detruire(matrice_t matrice) {
  if (matrice.tab != NULL) {
    free(matrice.tab);
  }
}

// Affichage d'une matrice
void matrice_afficher(matrice_t matrice) {
	for(int i = 0; i < matrice.nb_lignes; i++) {
		for (int j = 0; j < matrice.nb_colonnes; j++) {
			printf("%3d ", matrice.tab[i*matrice.nb_colonnes + j]);
		}
		printf("\n\n");
	}
}

// Multiplication de matrices
//
// Renvoie la matrice résultante de axb
// Si erreur la matrice est vide
matrice_t matrice_multiplier(matrice_t a, matrice_t b) {
	matrice_t res = matrice_creer();
	int somme;

	if (a.nb_colonnes == b.nb_lignes) {
		res.nb_lignes = a.nb_lignes;
		res.nb_colonnes = b.nb_colonnes;
		res.tab = malloc(res.nb_lignes * res.nb_colonnes * sizeof(char));

		for (int i = 0; i < res.nb_lignes; i++) {
			for (int j = 0; j < res.nb_colonnes; j++) {
				somme = 0;

				for (int k = 0; k < a.nb_colonnes; k++) {
					somme += a.tab[a.nb_colonnes * i + k] * b.tab[b.nb_colonnes * k + j];
				}

				res.tab[res.nb_colonnes * i + j] = somme;
			}
		}
	}

	return res;
}
