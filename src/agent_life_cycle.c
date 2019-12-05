#include <pthread.h>
/*
pthread_t pid[3];

void handler(int sig) {
	kill(pid[1], SIGSTOP);
}

int main() {
	int p1[2], p2[2], p3[2];

	signal(SIGINT, handler);

	pipe(p1);
	pipe(p2);
	pipe(p3);

	pid[0] = create(emeteur, p1);
	pid[1] = create(canal, p2);
	pid[2] = create(recepteur, p3);

	invoke(pid[0]);
	invoke(pid[1]); // Attend de lire la donnée envoyée par pid[0]
	invoke(pid[2]); // Attend de lire la donnée envoyée par pid[1]

	close(p1[0]);
	close(p2[0]);
	close(p2[1]);
	close(p3[1]);

	if (read(p3[0], &res, sizeof(res)) == -1) {
		fprintf(stderr, "Aucun agent ne peut écrire dans l'ordonanceur\n");
		exit(1);
	}
}*/

// Crée un thread
pthread_t create(void* (*fonction)(void* arg), void* arg) {
	pthread_t tread1;

	// Lancement du thread avec les arguments
	if (pthread_create(&thread1, NULL, fonction, arg)) {
		fprintf(stderr, "Erreur création pthread\n");
		exit(1);
	}

	return thread1;
}

void invoke(pthread_t pid) {
	kill(pid, SIGCONT);
}

void destroy(pthread_t pid) {
	kill(pid, SIGKILL);
}

void quit(pthread_t pid) {
	kill(pid, SIGTERM);
}
