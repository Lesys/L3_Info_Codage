#include <pthread.h>

void suspend(pthread_t pid)

void resume(pthread_t pid);

void wait(pthread_t pid);

void wake_up(pthread_t pid);
