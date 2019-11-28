#include <stdlib.h>
#include <stdio.h>

#include "../include/matrice.h"
#include "../include/pseudo_aleatoire.h"


int main() {
	matrice_t m1 = matrice_creer();

	m1.nb_lignes = 1;
	m1.nb_colonnes = 5;
	m1.tab = malloc(sizeof(*(m1.tab)) * m1.nb_lignes * m1.nb_colonnes);

	int i;
	for (i = 0; i < m1.nb_colonnes; i++)
		m1.tab[i] = 1;

	matrice_t m2 = matrice_creer();

	m2.nb_lignes = 1;
	m2.nb_colonnes = 3;
	m2.tab = malloc(sizeof(*(m2.tab)) * m2.nb_lignes * m2.nb_colonnes);

	for (i = 0; i < m2.nb_colonnes; i++)
		m2.tab[i] = 1;

	matrice_t m3 = matrice_creer();

	m3.nb_lignes = 1;
	m3.nb_colonnes = 4;
	m3.tab = malloc(sizeof(*(m3.tab)) * m3.nb_lignes * m3.nb_colonnes);

	for (i = 0; i < m3.nb_colonnes; i++)
		m3.tab[i] = 1;

	printf("M1: \n");
	matrice_afficher(m1);
	printf("M2: \n");
	matrice_afficher(m2);
	printf("M3: \n");
	matrice_afficher(m3);

	matrice_t p_gen = matrice_creer();
	p_gen.nb_lignes = 1;
	p_gen.nb_colonnes = 5;
	p_gen.tab = malloc(sizeof(*(p_gen.tab)) * p_gen.nb_lignes * p_gen.nb_colonnes);

	for (i = 0; i < p_gen.nb_colonnes; i++)
		p_gen.tab[i] = 0;

	VAL(p_gen, 0, 1) = 1;
	VAL(p_gen, 0, 4) = 1;

	matrice_t p_gen2 = matrice_creer();
	p_gen2.nb_lignes = 1;
	p_gen2.nb_colonnes = 3;
	p_gen2.tab = malloc(sizeof(*(p_gen2.tab)) * p_gen2.nb_lignes * p_gen2.nb_colonnes);

	for (i = 0; i < p_gen2.nb_colonnes; i++)
		p_gen2.tab[i] = 1;

	matrice_t p_gen3 = matrice_creer();
	p_gen3.nb_lignes = 1;
	p_gen3.nb_colonnes = 4;
	p_gen3.tab = malloc(sizeof(*(p_gen3.tab)) * p_gen3.nb_lignes * p_gen3.nb_colonnes);

	for (i = 0; i < p_gen3.nb_colonnes; i++)
		p_gen3.tab[i] = 0;

	VAL(p_gen3, 0, 0) = 1;
	VAL(p_gen3, 0, 2) = 1;

	matrice_t lm1 = code_longueur_max(m1, p_gen, 9);

	printf("Sequence longueur max pour m1 à 9: \n");
	matrice_afficher(lm1);

	matrice_t lm2 = code_longueur_max(m2, p_gen2, 4);

	printf("Sequence longueur max pour m2 à 4: \n");
	matrice_afficher(lm2);

	matrice_t lm3 = code_longueur_max(m3, p_gen3, 16);

	printf("Sequence longueur max pour m3 à 16: \n");
	matrice_afficher(lm3);

	printf("Fin des tests\n");

	matrice_detruire(m1);
	matrice_detruire(m2);
	matrice_detruire(m3);
	matrice_detruire(lm1);
	matrice_detruire(lm2);
	matrice_detruire(lm3);

	return 0;
}
