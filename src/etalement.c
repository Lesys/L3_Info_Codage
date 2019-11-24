#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/etalement.h"

// Affichage d'un message étalé
void msg_etale_afficher(msg_etale_t m) {
	for (int i = 0; i < m.taille_sequence * m.nb_sequences; i++) {
		printf(" %2d ", m.sequences[i]);
	}
	printf("\n");
}

// Ajout de deux messages étalés
//
// En cas d'erreur retourne un msg_etale_t avec un nombre de séquences égal à 0
msg_etale_t msg_etale_ajouter(msg_etale_t a, msg_etale_t b) {
	msg_etale_t res;

	if (a.taille_sequence != b.taille_sequence || a.nb_sequences != b.nb_sequences) {
		res.nb_sequences = 0;
		return res;
	}
	
	res.nb_sequences = a.nb_sequences;
	res.taille_sequence = a.taille_sequence;
	res.sequences = malloc(sizeof(char) * res.taille_sequence * res.nb_sequences);

	for (int i = 0; i < res.nb_sequences * res.taille_sequence; i++) {
		res.sequences[i] = a.sequences[i] + b.sequences[i];
	}

	return res;
} 

// Destruction d'un message étalé
void msg_etale_detruire(msg_etale_t m) {
	if (m.sequences) {
		free(m.sequences);
	}
}

// Etalement d'un message
// !!! Les numéros d'utilisateurs commencent à 0
msg_etale_t etalement(char * bits, matrice_t hadamard, int num_utilisateur) {
	msg_etale_t m;
	m.taille_sequence = hadamard.nb_colonnes;
	m.nb_sequences = strlen(bits);

	m.sequences = malloc(sizeof(char) * m.taille_sequence * m.nb_sequences);

	// Pointeur sur la position où l'on va écrire la prochaine séquence
	char * cur = m.sequences;
	// Pointeur sur la séquence de l'utilisateur
	char * base_seq = hadamard.tab + hadamard.nb_colonnes * num_utilisateur;
	int signe;

	for (int i = 0; i < m.nb_sequences; i++) {
		signe = bits[i] == '1' ? 1 : -1;
		
		for (int j = 0; j < m.taille_sequence; j++) {
			cur[j] = signe * base_seq[j];
		}
		cur += m.taille_sequence;
	}
	return m;
}

// Désetalement d'un message
// !!! Les numéros d'utilisateurs commencent à 0
char * desetalement(msg_etale_t m, matrice_t hadamard, int num_utilisateur) {
	// Pointeur sur la position où l'on va lire la prochaine séquence
	char * cur = m.sequences;
	// Pointeur sur la séquence de l'utilisateur
	char * base_seq = hadamard.tab + hadamard.nb_colonnes * num_utilisateur;
	int somme;
	// Message désetalé
	char * bits = malloc(m.nb_sequences + 1);
	
	for (int i = 0; i < m.nb_sequences; i++) {
		// Somme de la multiplication par la séquence de l'utilisateur
		somme = 0;
		for (int j = 0; j < m.taille_sequence; j++) {
			somme += cur[j] * base_seq[j];
		}
		// Division par le nombre d'utilisateurs
		somme /= hadamard.nb_lignes;

		bits[i] = somme == 1 ? '1' : '0';

		cur += m.taille_sequence;
	}
	
	bits[m.nb_sequences+1] = '\0';
	return bits;
}