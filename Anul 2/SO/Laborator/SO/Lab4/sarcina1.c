#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main() 
{
    
    pid_t pid = fork();
    if(pid < 0) 
    {
        perror("PID could not be created!\n");
        return errno;
    }else if (pid == 0)
    {
        printf("My PID = %d, Child PID = %d\n", getppid(), getpid());
        char *argv[] = {"la", NULL};
        execve("/bin/ls", argv, NULL);
        perror(NULL);
    }else 
    {
        wait(NULL);
        printf("Child %d finished!\n", getpid());
    }

    return 0;
}
