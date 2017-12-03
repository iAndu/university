#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int increase_count(int arg) {
    pthread_mutex_lock(&mtx);

    available_resources += arg;

    printf("Released %d resources, %d remaining.\n", arg, available_resources);    

    pthread_mutex_unlock(&mtx);

    return 0;
}

int decrease_count(int arg) {
    pthread_mutex_lock(&mtx);
        
    if (available_resources < arg) {
        return -1;
    } else {
        available_resources -= arg;
    }

    printf("Got %d resources, %d remaining.\n", arg, available_resources);

    pthread_mutex_unlock(&mtx);

    return 0;
}

void* routine(void* arg) {
    if (!decrease_count(*(int*)arg)) {
        increase_count(*(int*)arg);    
    }
}

int main() {
    if (pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    pthread_t threads[5];
    int i, values[5] = {2, 2, 3, 5, 2};

    for (i = 0; i < 5; ++i) {
        if (pthread_create(&threads[i], NULL, routine, (void*)&values[i])) {
            perror(NULL);
            return errno;
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (pthread_join(threads[i], NULL)) {
            perror(NULL);
            return errno;
        }
    }

    return 0;    
}