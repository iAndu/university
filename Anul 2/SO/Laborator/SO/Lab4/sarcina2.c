#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Child PID could not be created!\n");
        return errno;
    }else if(pid == 0) 
    {
        int n = 0, crt = 0;
        while (argv[1][crt] != NULL) 
        {
            n = n * 10 + (argv[1][crt] - '0');
            crt++;
        }
        while (n != 1) 
        {
            printf("%d ", n);
            if (n % 2 == 0) 
                n = n / 2;
            else 
                n = 3 * n + 1;

        }
        printf("%d\n", n);
    }else 
    {
        wait(NULL);
        printf("Child %d finished!\n", getpid());
    }

    return 0;
}
