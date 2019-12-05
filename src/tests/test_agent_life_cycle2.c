#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <agent_life_cycle.h>

#define MAX_BUFFER 2048

pthread_t pid[3];

typedef struct io_s {
	int entree;
	int sortie;
} io_t;

void * emetteur(void * args) {
	io_t * io = args;
	char buffer[MAX_BUFFER];
	int ind_buffer = 0;

	while (1) {
		while (read(io->entree, buffer + ind_buffer, 1) > 0) {
			if (buffer[ind_buffer] == '\0') {
				write(io->sortie, buffer, ind_buffer + 1);
				ind_buffer = 0;
			}
			else {
				ind_buffer++;
			}
		}
	}
}

void * canal(void * args) {
	io_t * io = args;
	char buffer[MAX_BUFFER];
	int ind_buffer = 0;

	while (1) {
		while (read(io->entree, buffer + ind_buffer, 1) > 0) {
			if (buffer[ind_buffer] == '\0') {
				write(io->sortie, buffer, ind_buffer + 1);
				ind_buffer = 0;
			}
			else {
				ind_buffer++;
			}
		}
	}
}


void * recepteur(void * args) {
	io_t * io = args;
	char buffer[MAX_BUFFER];
	int ind_buffer = 0;

	while (1) {
		while (read(io->entree, buffer + ind_buffer, 1) > 0) {
			if (buffer[ind_buffer] == '\0') {
				write(io->sortie, buffer, ind_buffer + 1);
				ind_buffer = 0;
			}
			else {
				ind_buffer++;
			}
		}
	}
}

int main() {
    int p[4][2];

    for (int i = 0; i < 4; i++) {
    	pipe(p[i]);
    	fcntl(p[i][0], F_SETFL, fcntl(p[i][0], F_GETFL) | O_NONBLOCK);
    }

    io_t io_emetteur, io_canal, io_recepteur;
    io_emetteur.entree = p[0][0];
    io_emetteur.sortie = p[1][1];
    io_canal.entree = p[1][0];
    io_canal.sortie = p[2][1];
    io_recepteur.entree = p[2][0];
    io_recepteur.sortie = p[3][1];

    int entree = p[0][1];
    int sortie = p[3][0];

	pid[0] = create(emetteur, &io_emetteur);
	pid[1] = create(canal, &io_canal);
	pid[2] = create(recepteur, &io_recepteur);

	char buffer[MAX_BUFFER];
	int ind_buffer = 0;

	for (int i = 0; i < 10; i++) {
		if (i == 0) {
			write(entree, "blablabla", 10);
		}
		else if (i == 5) {
			write(entree, "blobloblo", 10);
		}

		while (read(sortie, buffer + ind_buffer, 1) > 0) {
			if (buffer[ind_buffer] == '\0') {
				printf("%s\n", buffer);
				ind_buffer = 0;
			}
			else {
				ind_buffer++;
			}
		}
		sleep(1);
	}
}
