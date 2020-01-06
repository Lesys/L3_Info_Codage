#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>

void stop_handler(int pid) {

	sigset_t mask, old_mask;
	sigemptyset(&mask);
	int i = 0;

	for (i = 0; i < NSIG; i++)
		if (i != SIGUSR2)
			sigaddset(&mask, i);

	sigprocmask(SIG_SETMASK, &mask, &old_mask);

	pause();

	sigprocmask(SIG_SETMASK, &old_mask, NULL);
	signal(SIGUSR1, stop_handler);
}

void continue_handler(int pid) {
	signal(SIGUSR2, continue_handler);
}


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
	pthread_kill(pid, SIGUSR2);
}

void destroy(pthread_t pid) {
	pthread_kill(pid, SIGKILL);
}

void quit(pthread_t pid) {
	pthread_kill(pid, SIGTERM);
}

void suspend(pthread_t pid) {
	pthread_kill(pid, SIGUSR1);
}

void resume(pthread_t pid) {
	pthread_kill(pid, SIGUSR2);
}

void wait2(pthread_t pid) {
	pthread_kill(pid, SIGUSR1);
}

void wake_up(pthread_t pid) {
	pthread_kill(pid, SIGUSR2);
}
