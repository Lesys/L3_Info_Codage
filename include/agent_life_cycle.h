#include <pthread.h>

pthread_t create(void* (*fonction)(void* arg), void* arg);

void invoke(pthread_t pid);

void destroy(pthread_t pid);

void quit(pthread_t pid);

void suspend(pthread_t pid);

void resume(pthread_t pid);

void wait(pthread_t pid);

void wake_up(pthread_t pid);
