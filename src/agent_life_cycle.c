#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>

void stop_handler(int pid) {
	fprintf(stderr, "Je bloque le signal %d\n", pid);

	sigset_t mask, old_mask;
	sigemptyset(&mask);
	int i = 0;

	for (i = 0; i < NSIG; i++)
		if (i != SIGCONT)
			sigaddset(&mask, i);

	sigprocmask(SIG_SETMASK, &mask, &old_mask);

	pause();

	sigprocmask(SIG_SETMASK, &old_mask, NULL);
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
	kill(pid, SIGCONT);
}

void destroy(pthread_t pid) {
	kill(pid, SIGKILL);
}

void quit(pthread_t pid) {
	kill(pid, SIGTERM);
}

void suspend(pthread_t pid) {
	sigset_t mask, old_mask;
	sigemptyset(&mask);
	int i = 0;

	for (i = 0; i < NSIG; i++)
		if (i != SIGCONT)
			sigaddset(&mask, i);

	sigprocmask(SIG_SETMASK, &mask, &old_mask);

	kill(pid, SIGSTOP);

	sigprocmask(SIG_SETMASK, &old_mask, NULL);
//	kill(pid, SIGSTOP);
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
