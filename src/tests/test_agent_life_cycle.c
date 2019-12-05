#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include <agent_life_cycle.h>

pthread_t pid[3];

void handler(int sig) {
        kill(pid[0], SIGKILL);
        kill(pid[1], SIGKILL);
        kill(pid[2], SIGKILL);

	exit(0);
}

void emeteur(int* pipe) {
	//close(pipe[0]);
	while (1) {
		printf("Bonjour\n");
		sleep(2);
	}
}

void* emeteur_callback(void* pipe) {
	emeteur(pipe);
}

void canal(int* pipe) {
	//close(pipe[0]);
	while (1) {
		printf("Ici le canal\n");
		sleep(2);
	}
}

void* canal_callback(void* pipe) {
	canal(pipe);
}

void recepteur(int* pipe) {
	close(pipe[0]);

	printf("Pipe rec: %d\n", pipe[1]);
	int envoi = 15;

//	write(pipe[1], &envoi, sizeof(envoi));
	write(pipe[1], "BONJOUR SALOW", strlen("BONJOUR SALOW"));
	while (1) {
//		envoi++;
		printf("Au revoir\n");
		sleep(2);
//		write(pipe[1], &envoi, sizeof(envoi));
	}
}

void* recepteur_callback(void* pipe) {
	recepteur(pipe);
}

int main() {
        int p1[2], p2[2], p3[2], p[2];

        signal(SIGINT, handler);

	char res;
//	char* res = malloc(sizeof(char) * 14);
//	int res = 12;

	pipe(p);
        pipe(p1);
        pipe(p2);
        pipe(p3);

	int p_temp = p[1];
//	p[1] = p1[1];
//	p[0] = p3[0];
	p1[1] = p2[1];
	p2[1] = p3[1];
	p3[1] = p_temp;

/*        pid[0] = create(emeteur_callback, p1);
        pid[1] = create(canal_callback, p2);
        pid[2] = create(recepteur_callback, p);
*/
//        invoke(pid[0]);
 //       invoke(pid[1]); // Attend de lire la donnée envoyée par pid[0]
  //      invoke(pid[2]); // Attend de lire la donnée envoyée par pid[1]

/*        close(p1[0]);
        close(p2[0]);
        close(p2[1]);
        close(p3[0]);
        close(p3[1]);
//	close(p[1]);*/
	int err, i;
	switch(fork()) {
		case 0: fprintf(stderr, "Je suis le fils\n");
			write(p[1], "BONJOUR SALOW", strlen("BONJOUR SALOW"));
			exit(1);
	}

	while (wait(NULL) != -1);
	fprintf(stderr, "Avant while\n");
	while (read(p[0], &res, 1) > 0)
		fprintf(stderr, "Message: %c\n", res);

	fprintf(stderr, "Après while\n");
//            write(STDOUT_FILENO, &res, 1);

//	while (1) {
/*
		for (i = 0; (err = (read(p[0], &res, sizeof(res))) != -1 && err != 0) && i < 3; i++) {
			printf("Pipe main: %d\n", p[0]);
	//		printf("%ld\n", read(p[0], &res, sizeof(char)));
			printf("Résultat main: %d, lu: %d\n", res, err);
		}

		if (err == -1)
			fprintf(stderr, "Erreur: %d\n", err);
		else
			fprintf(stderr, "pas d'erreur\n");
	}*/
/*	if (read(p3[0], &res, sizeof(char)) == -1) {
                fprintf(stderr, "Aucun agent ne peut écrire dans l'ordonanceur: %c\n", res);
                exit(1);
        }
*/
	while (1);

	return 0;
}
