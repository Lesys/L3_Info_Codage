#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrice.h"
#include "hadamard.h"

#define NB_USERS_MIN 1
#define NB_USERS_MAX 16
#define TAILLE_MAX_MESSAGE 256

int transformer_message_bit(char* message, char** bits) {
	*bits = malloc(sizeof(**bits) * strlen(message) * 8 + 1);
fprintf(stderr, "%d caractères alloués\n", sizeof(**bits) * (strlen(message) + 1) * 8);
	int i, j;
	for (i = 0; i < (strlen(message) + 1) * 8 && message[i] != '\0'; i++) {
		for (j = 7; j >= 0; j--) {
			fprintf(stderr, "cara: %c, binaire: %c, indice bits: %d\n", message[i], message[i] & (1 << j)? '1' : '0', i * 8 + (7 - j));
			*bits[i * 8 + (7 - j)] = 'h';//(message[i] & (1 << j)? '1' : '0');
			fprintf(stderr, "Valeur dans bits: %c\n", *bits[i * 8 + (7 - j)]);
		}

//		*bits[i * 8 + j] = '\0';
//		printf("%s\n", *bits + i * 8);
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Nombre de paramètres incorrects: %s <nb_utilisateurs>\n", argv[0]);
		exit(1);
	}

	int nb_users = atoi(argv[1]);

	if (nb_users < NB_USERS_MIN || nb_users > NB_USERS_MAX) {
		fprintf(stderr, "Le nombre d'utilisateurs est incorrect (1 <= nb_utilisateur <= 16, valeur actuelle: %d\n)", nb_users);
		exit(2);
	}

	// Récupère le numéro de la matrice à générer (un entier)
	int num_matrice = ceil(log2((double)nb_users));
	// Nombre de lignes (et colonnes) de la matrice
	int nb_lignes = pow(2, num_matrice);
	// Matrice d'Hadamard générée par la fonction
	matrice_t hadam_matrice;
	hadamard_matrice(num_matrice, &hadam_matrice);
	afficher_matrice(hadam_matrice);

	char* message = malloc(sizeof(*message) * TAILLE_MAX_MESSAGE);
	printf("Message à envoyer: ");
	scanf("%s", message);
	message = realloc(message, strlen(message) + 1);

	// Récup du message d'un utilisateur: (message_etale * (sequence_utilisateur)T)/nb_lignes
	char* bits = NULL;

	transformer_message_bit(message, &bits);


	free(bits);
	free(message);
	return 0;
}
