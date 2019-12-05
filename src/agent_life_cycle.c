#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>

// Crée un thread
pthread_t create(void* (*fonction)(void* arg), void* arg) {
	pthread_t thread1;

	// Lancement du thread avec les arguments
	if (pthread_create(&thread1, NULL, fonction, arg)) {
		fprintf(stderr, "Erreur création pthread\n");
		exit(1);
	}

	printf("Création pthread %ld\n", thread1);
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

void suspend(pthread_t pid) {
	kill(pid, SIGSTOP);
}

void resume(pthread_t pid) {
	kill(pid, SIGCONT);
}

void wait2(pthread_t pid) {
	kill(pid, SIGSTOP);
}

void wake_up(pthread_t pid) {
	kill(pid, SIGCONT);
}
