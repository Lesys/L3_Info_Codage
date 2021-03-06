#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <pseudo_aleatoire.h>
#include <matrice.h>

//char* pseudo_aleat_generer

// Génère un code JPL (pour faire plusieurs fois, reprendre le résultat et ajouter la nouvelle séquence)
matrice_t code_jpl(matrice_t seq_1, matrice_t seq_2, int longueur) {
	// S'ils ne sont pas premier entre eux
	if (seq_1.nb_colonnes % seq_2.nb_colonnes == 0 || seq_2.nb_colonnes % seq_1.nb_colonnes == 0) {
		fprintf(stderr, "Erreur code_jpl: longueur de la première séquence non première avec longueur de la seconde séquence (%d et %d)\n", seq_1.nb_colonnes, seq_2.nb_colonnes);
		exit(1);
	}

//	int n = ppcm(seq_1.nb_colonnes, seq_2.nb_colonnes);
	int i;
	matrice_t seq_finale = matrice_creer();
	seq_finale.tab = malloc(sizeof(char) * longueur);
	seq_finale.nb_lignes = 1;
	seq_finale.nb_colonnes = longueur;

	// Prend le XOR de la valeur de la première séquence (répétition simulée avec le %) et de la seconde séquence (pareil)
	for (i = 0; i < longueur; i++)
		VAL(seq_finale, 0, i) = XOR(VAL(seq_1, 0, i % seq_1.nb_colonnes), VAL(seq_2, 0, i % seq_2.nb_colonnes));

	return seq_finale;
}

// Génère un code de gold
matrice_t code_gold(matrice_t seq_initiale1, matrice_t seq_xor1, matrice_t seq_initiale2, matrice_t seq_xor2, int longueur) {
/*	printf("Dans gold\n");

	printf("Première matrice initiale: ");
	matrice_afficher(seq_initiale1);
	printf("Seconde matrice initiale: ");
	matrice_afficher(seq_initiale2);
	printf("Premièr xor initial: ");
	matrice_afficher(seq_xor1);
	printf("Second xor initial: ");
	matrice_afficher(seq_xor2);

*/
	matrice_t seq_1 = code_longueur_max(seq_initiale1, seq_xor1, longueur);
	matrice_t seq_2 = code_longueur_max(seq_initiale2, seq_xor2, longueur);
	int i;

	matrice_t seq_finale = matrice_creer();
	seq_finale.tab = malloc(sizeof(char) * longueur);
	seq_finale.nb_lignes = 1;
	seq_finale.nb_colonnes = longueur;
/*
	printf("Première matrice gold: ");
	matrice_afficher(seq_1);
	printf("Seconde matrice gold: ");
	matrice_afficher(seq_2);
*/
	for (i = 0; i < longueur; i++)
		VAL(seq_finale, 0, i) = XOR(VAL(seq_1, 0, i), VAL(seq_2, 0, i));

/*	for (i = 0; i < longueur; i++)
		printf("%d ", VAL(seq_finale, 0, i));


	printf("Sequence finale: ");
	matrice_afficher(seq_finale);

	printf("Fin gold\n");
*/

	matrice_detruire(seq_1);
	matrice_detruire(seq_2);
	return seq_finale;
}

// Génère un code à longueur maximale
matrice_t code_longueur_max(matrice_t seq_initiale, matrice_t seq_xor, int longueur) {
	if (seq_initiale.nb_colonnes != seq_xor.nb_colonnes) {
		fprintf(stderr, "Erreur code_longueur_max: longueur de la séquence initiale différente du polynome de génération\n");
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
//	VAL(sequence, 0, longueur + 1) = '\0';

	matrice_detruire(seq_old);
	matrice_detruire(seq_new);

	return sequence;
}
