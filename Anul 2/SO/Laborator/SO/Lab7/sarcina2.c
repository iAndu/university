#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

sem_t sem;
int count;

void* barrier_point(void *arg) {
    count++;
    printf("%d reached the barrier\n", *((int*)arg));

    // If the expected number of threads reached thebarrier, post so
    // threads waiting can be released
    if(count == 5) {
        if(sem_post(&sem)) {
            perror(NULL);
            return (void*)&errno;
        }
    }

    // Put thread to wait until it gets a post
    if(sem_wait(&sem)) {
        perror(NULL);
        return (void*)&errno;
    }

    // When thread is released, post so the next one can go
    if (sem_post(&sem)) {
        perror(NULL);
        return (void*)&errno;
    }

    printf("%d passed the barrier\n", *((int*)arg));

    return NULL;
}

int main() {
    pthread_t thr[5];
    
    if(sem_init(&sem, 0, 0)) {
        perror(NULL);
        return errno;
    }

    int i;
    for(i = 0; i < 5; i++) {
        // Create a thread number associated to the one being created
        int *nr = malloc(sizeof(int));
        *nr = i;

        if(pthread_create(&thr[i], NULL, barrier_point, (void*)nr)) {
            perror(NULL);
            return errno;
        }
    }
    
    void *result;
    // Wait for threads to finish
    for(i = 0 ; i < 5; i++) {
        if(pthread_join(thr[i], &result)) {
            perror(NULL);
            return errno;
        }
    }
    
    return 0;
}
