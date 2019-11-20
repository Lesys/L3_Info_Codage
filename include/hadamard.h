#ifndef HADAMARD_H
#define HADAMARD_H

typedef struct {
	char * tab;
	int largeur;
} matrice_t;

void afficher_matrice(matrice_t matrice);


int hadamard_matrice(int n, matrice_t * matrice);

#endif
