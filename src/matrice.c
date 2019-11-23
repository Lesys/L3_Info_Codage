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

// Matrice identité N
matrice_t matrice_identite(int n) {
	matrice_t identite = matrice_creer();
	identite.nb_lignes = identite.nb_colonnes = n;
	identite.tab = malloc(sizeof(char) * n * n);

	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			identite.tab[n * i + j] = i == j? 1 : 0;

	return identite;
}

// Transposée d'une matrice
matrice_t matrice_transposee(matrice_t matrice) {
	matrice_t transp = matrice_creer();
	transp.nb_lignes = matrice.nb_colonnes;
	transp.nb_colonnes = matrice.nb_lignes;
	transp.tab = malloc(sizeof(char) * transp.nb_lignes * transp.nb_colonnes);

	int i, j;
	for (i = 0; i < matrice.nb_lignes; i++)
		for (j = 0; j < matrice.nb_colonnes; j++) {
			transp.tab[transp.nb_colonnes * j + i] = matrice.tab[matrice.nb_colonnes * i + j];
			printf("%d ", matrice.tab[matrice.nb_colonnes * i + j]);
		}

	return transp;
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
