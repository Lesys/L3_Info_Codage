#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/pseudo_aleatoire.h"
#include "../include/matrice.h"

//char* pseudo_aleat_generer

// Génère un code à longueur maximale
matrice_t code_longueur_max(matrice_t seq_initiale, matrice_t seq_xor, int longueur) {
	if (seq_initiale.nb_colonnes != seq_xor.nb_colonnes) {
		fprintf(stderr, "Erreur: longueur de la séquence initiale différente du polynome de génération\n");
		exit(1);
	}

/*	fprintf(stderr, "Sequence initiale: ");
	matrice_afficher(seq_initiale);
	fprintf(stderr, "Polynôme générateur: ");
	matrice_afficher(seq_xor);
*/
	int i, j;
	// Taille de la séquence == nombre de bits (+1 pour \0)
	matrice_t sequence = matrice_creer(), seq_old = matrice_creer(), seq_new = matrice_creer();
	sequence.nb_lignes = 1;
	sequence.nb_colonnes = longueur;
	sequence.tab = malloc(sizeof(char) * (longueur + 1));
	seq_old.tab = malloc(sizeof(char) * seq_initiale.nb_colonnes), seq_new.tab = malloc(sizeof(char) * seq_initiale.nb_colonnes);
	seq_old.nb_lignes = seq_new.nb_lignes = seq_initiale.nb_lignes;
	seq_old.nb_colonnes = seq_new.nb_colonnes = seq_initiale.nb_colonnes;

	for (j = 0; j < seq_initiale.nb_colonnes; j++) {
		VAL(seq_old, 0, j) = VAL(seq_initiale, 0, j);
		VAL(sequence, 0, j) = 0;
//		fprintf(stderr, "Valeur recopiée: %d\n", VAL(seq_old, 0, j));
	}

	// Calcul des différentes registres intermédiaires (pour la longueur demandée)
	for (i = 0; i < longueur; i++) {
//		fprintf(stderr, "Matrice old: ");
//		matrice_afficher(seq_old);
		// Recopie du dernier bit des registres intermédiaires
//		printf("Valeur ajoutée dans sequence: %d\n", VAL(sequence, 0, i) = VAL(seq_old, 0, seq_old.nb_colonnes - 1));

//fprintf(stderr, "Matrice sequence: ");
//matrice_afficher(sequence);

		VAL(seq_new, 0, 0) = 0;
		// Recopie et décalage des bits (sauf le premier qui est calculé avec XOR)
		for (j = 0; j <= seq_old.nb_colonnes - 1; j++) {
			// Si on doit faire le xor sur le bit
			if (VAL(seq_xor, 0, j) == 1) {
				VAL(seq_new, 0, 0) = XOR(VAL(seq_new, 0, 0), VAL(seq_old, 0, j));
//				fprintf(stderr, "valeur du xor pour %d %d: %c\n", i, j, XOR(VAL(seq_new, 0, 0), VAL(seq_old, 0, j)));
//				fprintf(stderr, "Nouvelle valeur de seq_new: %c\n", VAL(seq_new, 0, 0));
			}

			// Recopie des bits après le premier
			if (j + 1 <= seq_old.nb_colonnes - 1) {
				VAL(seq_new, 0, j + 1) = VAL(seq_old, 0, j);
//				fprintf(stderr, "Val en j+1: %c", VAL(seq_new, 0, j + 1));
			}

		}

//		fprintf(stderr, "sequence nouvelle :");
//		matrice_afficher(seq_new);

		// Recopie du dernier bit du registre actuel
		VAL(sequence, 0, i) = VAL(seq_old, 0, seq_old.nb_colonnes - 1);

		// Recopie de la nouvelle séquence dans l'ancienne pour boucler
		for (j = 0; j < seq_new.nb_colonnes; j++)
			VAL(seq_old, 0, j) = VAL(seq_new, 0, j);

	}

	// Recopie du dernier bit du dernier registre intermédiaire
	VAL(sequence, 0, i) = VAL(seq_old, 0, seq_old.nb_colonnes - 1);
	VAL(sequence, 0, longueur + 1) = '\0';

	matrice_detruire(seq_old);
	matrice_detruire(seq_new);

	return sequence;
}
