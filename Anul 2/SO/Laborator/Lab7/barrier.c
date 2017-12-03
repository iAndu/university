#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 5

int s = 0;
int released = 0;
pthread_mutex_t mtx;

void barrier_point() {
    pthread_mutex_lock(&mtx);
    ++s;
    if (s == MAX_THREADS) {
        released = 1;
    }
    pthread_mutex_unlock(&mtx);

    while (!released);
}

void* tfun(void *v) {
    int *tid = (int*)v;

    printf("%d reached the barrier\n", *tid);
    barrier_point();
    printf("%d passed the barrier\n", *tid);

    // free(tid);

    return NULL;
}

int main() {
    pthread_t threads[MAX_THREADS];

    if (pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    int i, tids[MAX_THREADS] = {0, 1, 2, 3, 4};

    for (i = 0; i < MAX_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, tfun, (void*)&tids[i])) {
            perror(NULL);
            return errno;
        }
    }

    for (i = 0; i < MAX_THREADS; ++i) {
        if (pthread_join(threads[i], NULL)) {
            perror(NULL);
            return errno;
        }
    }

    return 0;
}