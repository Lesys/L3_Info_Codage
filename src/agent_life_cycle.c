#include <pthread.h>
#include <signal.h>

void suspend(pthread_t pid) {
	kill(pid, SIGSTOP);
}

void resume(pthread_t pid) {
	kill(pid, SIGCONT);
}

void wait(pthread_t pid) {
	kill(pid, SIGSTOP);
}

void wake_up(pthread_t pid) {
	kill(pid, SIGCONT);
}

