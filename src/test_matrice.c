#include <stdlib.h>
#include <stdio.h>

#include "../include/matrice.h"


int main() {
	matrice_t m1 = matrice_creer();

	m1.nb_lignes = 2;
	m1.nb_colonnes = 5;
	m1.tab = malloc(sizeof(*(m1.tab)) * m1.nb_lignes * m1.nb_colonnes);

	m1.tab[0] = 4;
	m1.tab[1] = 7;
	m1.tab[2] = 1;
	m1.tab[3] = 8;
	m1.tab[4] = 4;
	m1.tab[5] = 2;
	m1.tab[6] = 9;
	m1.tab[7] = 0;
	m1.tab[8] = 0;
	m1.tab[9] = 2;

	matrice_t m2 = matrice_creer();

	m2.nb_lignes = 5;
	m2.nb_colonnes = 1;
	m2.tab = malloc(sizeof(*(m2.tab)) * m2.nb_lignes * m2.nb_colonnes);

	m2.tab[0] = 1;
	m2.tab[1] = 5;
	m2.tab[2] = 2;
	m2.tab[3] = 6;
	m2.tab[4] = 0;

	matrice_t m3 = matrice_creer();

	m3.nb_lignes = 2;
	m3.nb_colonnes = 2;
	m3.tab = malloc(sizeof(*(m3.tab)) * m3.nb_lignes * m3.nb_colonnes);

	m3.tab[0] = 5;
	m3.tab[1] = 4;
	m3.tab[2] = 2;
	m3.tab[3] = 9;

	printf("M1: \n");
	matrice_afficher(m1);
	printf("M2: \n");
	matrice_afficher(m2);
	printf("M3: \n");
	matrice_afficher(m3);

	matrice_t m_mult = matrice_multiplier(m1, m2);

	printf("M1 * M2: \n");
	matrice_afficher(m_mult);

	matrice_t m3m3 = matrice_multiplier(m3, m3);

	printf("M3 * M3: \n");
	matrice_afficher(m3m3);

	printf("Fin des tests\n");

	int n;
	printf("Taille matrice identité: ");
	scanf("%d", &n);
	matrice_t id = matrice_identite(n);
	printf("Matrice identité %d:\n", n);
	matrice_afficher(id);

	matrice_t t = matrice_transposee(m1);
	printf("Transposée de M1:\n");
	matrice_afficher(t);



	printf("Valeur de M1[2][3]: %d", VAL(m1, 2, 5));
	matrice_detruire(m1);
	matrice_detruire(m2);
	matrice_detruire(m_mult);
	matrice_detruire(m3m3);
	matrice_detruire(id);
	matrice_detruire(t);

	return 0;
}
