#ifndef MATRICE_H
#define MATRICE_H

#define VAL(matrice, x, y) matrice.tab[x * matrice.nb_colonnes + y]

typedef struct matrice_s {
	char * tab;
	int nb_colonnes;
	int nb_lignes;
} matrice_t;

// Création d'une nouvelle matrice
matrice_t matrice_creer();

// Destruction d'une matrice
void matrice_detruire(matrice_t matrice);

// Matrice identité N
matrice_t matrice_identite(int n);

// Transposée d'une matrice
matrice_t matrice_transposee(matrice_t matrice);

// Affichage d'une matrice
void matrice_afficher(matrice_t matrice);

// Multiplication de matrices
matrice_t matrice_multiplier(matrice_t a, matrice_t b);

#endif
