#ifndef MATRICE_H
#define MATRICE_H

typedef struct {
	char * tab;
	int nb_colonnes;
  int nb_lignes;
} matrice_t;

// Création d'une nouvelle matrice
matrice_t creer_matrice();

// Destruction d'une matrice
void detruire_matrice(matrice_t matrice);

// Affichage d'une matrice
void afficher_matrice(matrice_t matrice);

// Multiplication de matrices
matrice_t multiplier_matrice(matrice_t a, matrice_t b);

#endif
