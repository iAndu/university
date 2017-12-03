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

int decrease_count(int arg) 
{
    pthread_mutex_lock(&mtx);
        
    if (available_resources < arg)
        return -1;
    else 
        available_resources -= arg;

    printf("Got %d resources, %d remaining.\n", arg, available_resources);

    pthread_mutex_unlock(&mtx);

    return 0;
}

void *verif(void* arg) 
{
    if (!decrease_count(*(int*)arg)) 
    {
        increase_count(*(int*)arg);    
    }
}

int main() 
{
    if (pthread_mutex_init(&mtx, NULL)) 
    {
        perror("The mutex could not be created!\n");
        return errno;
    }

    pthread_t thr[5];
    int i, values[5] = {1, 1, 1, 1, 1};

    for (i = 0; i < 5; ++i) 
    {
        if (pthread_create(&thr[i], NULL, verif, (void*)&values[i])) 
	{
            perror("The thread could not be created!\n");
            return errno;
        }
    }

    for (int i = 0; i < 5; ++i) 
    {
        if (pthread_join(thr[i], NULL)) 
	{
            perror("The thread could not be waited!\n");
            return errno;
        }
    }

    return 0;    
}
