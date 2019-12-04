#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <matrice.h>
#include <hadamard.h>
#include <etalement.h>
#include <binaire_formate.h>

#define NB_USERS_MIN 1
#define NB_USERS_MAX 16
#define TAILLE_MAX_MESSAGE 256

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Nombre de paramètres incorrects: %s <nb_utilisateurs> <num_utilisateur>\n", argv[0]);
		exit(1);
	}

	int nb_users = atoi(argv[1]);
	int num_user = atoi(argv[2]);

	if (nb_users < NB_USERS_MIN || nb_users > NB_USERS_MAX) {
		fprintf(stderr, "Le nombre d'utilisateurs est incorrect (%d <= nb_utilisateurs <= %d, valeur actuelle: %d\n)", NB_USERS_MIN, NB_USERS_MAX, nb_users);
		exit(2);
	}

	// Récupère le numéro de la matrice à générer (un entier)
	int num_matrice = ceil(log2((double)nb_users));
	// Nombre de lignes (et colonnes) de la matrice
	int nb_lignes = pow(2, num_matrice);

	// Si le numéro utilisateur n'est pas dans la matrice d'hadamard
	if (num_user < NB_USERS_MIN - 1 || num_user > nb_lignes - 1) {
		fprintf(stderr, "Le numéro d'utilisateur est incorrect (%d <= num_utilisateur <= %d, valeur actuelle: %d\n)", NB_USERS_MIN, nb_lignes, num_user);
		exit(3);
	}



	// Matrice d'Hadamard générée par la fonction
	matrice_t hadam_matrice;
	hadamard_matrice(num_matrice, &hadam_matrice);
	matrice_afficher(hadam_matrice);

/*	char* message = malloc(sizeof(*message) * TAILLE_MAX_MESSAGE);
	printf("Message à envoyer: ");
	scanf("%[^\n]", message);
	message = realloc(message, strlen(message) + 1);
*/
	// Récup du message d'un utilisateur: (message_etale * (sequence_utilisateur)T)/nb_lignes
	bf_t bits = transformer_donnee_bit("a", 1);
	bf_t bits2 = transformer_donnee_bit("b", 1);
	bf_t bits3 = transformer_donnee_bit("c", 1);
//	fprintf(stderr, "\nTransformation en bits: %s\n", bits);

	// Test etalement
	msg_etale_t m, m1, m2, m3;
/*
	matrice_t hadam;
	printf("\n\nTest Etalement :\n\n");
	hadamard_matrice(3, &hadam);
	m1 = etalement("101", hadam, 1);
	printf("Message 1 :\n101\nMessage 1 etale :\n");
	msg_etale_afficher(m1);
	m2 = etalement("011", hadam, 3);
	printf("Message 2 :\n011\nMessage 2 etale :\n");
	msg_etale_afficher(m2);
	m = msg_etale_ajouter(m1, m2);
	printf("Somme message 1 et 2 :\n");
	msg_etale_afficher(m);
	printf("Message 1 desetale :\n");
	printf("%s\n", desetalement(m, hadam, 1));
	printf("Message 2 desetale :\n");
	printf("%s\n", desetalement(m, hadam, 3));
*/

	m1 = etalement(bits, hadam_matrice, num_user);
//	msg_etale_afficher(m1);

//	printf("Ajout du même message\n");
	m2 = etalement(bits2, hadam_matrice, 1);
	m3 = etalement(bits3, hadam_matrice, 2);
//	msg_etale_afficher(m2);
	m = msg_etale_ajouter(m1, m2);
	m = msg_etale_ajouter(m, m3);
	printf("Message final: ");
	msg_etale_afficher(m);

	printf("Message 1 desetale :\n");
	printf("%s\n", desetalement(m, hadam_matrice, num_user));

	char* msg1 = transformer_bit_donnee(desetalement(m, hadam_matrice, num_user));
	char* msg2 = transformer_bit_donnee(desetalement(m, hadam_matrice, 1));
	char* msg3 = transformer_bit_donnee(desetalement(m, hadam_matrice, 2));

	printf("Message 1: %s\nMessage 2: %s\nMessage 3: %s\n", msg1, msg2, msg3);

	msg_etale_detruire(m);
	msg_etale_detruire(m1);
	msg_etale_detruire(m2);
	free(msg1);
	free(msg2);
	free(msg3);
	free(bits);
	free(bits2);
	free(bits3);
//	free(message);

	matrice_detruire(hadam_matrice);

	return 0;
}
