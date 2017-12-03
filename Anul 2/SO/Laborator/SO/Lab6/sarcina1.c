#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void* reverseString(void* argc)
{
    char *str = (char*)argc;
    char *rstr;
    int len = strlen(str);
    rstr = malloc(len * sizeof(char));
    int i;

    for(i = len - 1; i >= 0; i--)
    {
        rstr[len - i - 1] = str[i];
    }
    return (void*)rstr;
}

int main(int argc, char *argv[])
{
    pthread_t thr;
    void *result;
    if(pthread_create(&thr, NULL, reverseString, argv[1]))
    {
        perror("The thread could not be created!\n");
        return errno;
    }
    if(pthread_join(thr, &result)){
        perror("The thread could not be waited!\n");
        return errno;
    }

    printf("%s\n", (char*)result);

    return 0;
}
