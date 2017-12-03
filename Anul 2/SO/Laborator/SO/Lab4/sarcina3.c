#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
   int i;
   printf("Start Parent %d\n", getpid());
   for(i = 1; i < argc; i++) 
   {
        pid_t pid = fork();
        if(pid < 0) 
        {
            perror("Child PID could not be created!\n");
            return errno;
        }else if (pid == 0)
        {
            int n = 0, crt = 0;
            while (argv[i][crt] != NULL)
            {
                n = n * 10 + (argv[i][crt] - '0');
                crt++;
            }
            printf("%d: ", n);
            while (n != 1)
            {
                printf("%d ", n);
                if (n % 2 == 0)
                    n = n / 2;
                else
                    n = 3 * n + 1;
                
            }
            printf("%d\n", n);
            printf("Done Parent %d Me %d\n", getppid(), getpid()); 
            return 0;
        }
   }

   for(i = 1; i < argc; i++) 
   {
       wait(NULL);
   }

   printf("Done Parent %d Me %d\n", getppid(), getpid());
        
    return 0;
}
