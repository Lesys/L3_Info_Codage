#ifndef MATRICE_H
#define MATRICE_H

typedef struct {
	char * tab;
	int nb_colonnes;
  int nb_lignes;
} matrice_t;

// Création d'une nouvelle matrice
matrice_t matrice_creer();

// Destruction d'une matrice
void matrice_detruire(matrice_t matrice);

// Affichage d'une matrice
void matrice_afficher(matrice_t matrice);

// Multiplication de matrices
matrice_t matrice_multiplier(matrice_t a, matrice_t b);

#endif
