#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include<stdlib.h>

int A[3][2] = { {1, 2}, 
              {3, 4}, 
              {5, 6}};
int B[2][3] = { {1, 2, 3},
              {4, 5, 6}};

int C[3][3];

struct data 
{
    int x;
    int y;
};

void *calculateMat(void *arg) 
{
    
    struct data foo = *((struct data*)arg);
    int *result;
    result = malloc(sizeof(int));
    int i;
    for(i = 0; i < 2; i++) 
    {
        *result += A[foo.x][i] * B[i][foo.y];
    }

    return (void*)result;
}

int main() 
{
    pthread_t thr[9];
    int cnt = 0;
    int i, j;
    for(i = 0; i < 3; i++) 
    {
        for(j = 0; j < 3; j++){
            struct data arg;
            arg.x = i; 
            arg.y = j;
            if(pthread_create(&thr[cnt], NULL, calculateMat, (void*)&arg))
            {
                 perror("The thread could not be created!\n");
                 return errno;
            }
            cnt++;
        }
    }
    
    void *result;
    for (i = 0; i < 9; i++) 
    {
        if(pthread_join(thr[i], &result))
        {
            perror("The thread could not be created!\n");
            return errno;
        }
        C[i / 3][i % 3] = *((int*)result);
    }
    
    for(i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
