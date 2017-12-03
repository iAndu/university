#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int filedesc1 = open(argv[1], O_RDONLY);
    if(filedesc1 == -1) 
    {
        perror("First file could not be opened!\n");
        return errno;
    }
    int filedesc2 = open(argv[2], O_WRONLY | O_APPEND | O_CREAT | O_TRUNC);
    if(filedesc2 == -1)
    {
        perror("Second file could not be opened!\n");
        return errno;
    }
   
    struct stat sb;
    if(stat(argv[1], &sb))
    {
        perror("First file could not be descripted!\n");
        return errno;
    } 

    char *buf;
    buf = malloc(sb.st_size);
    int nread, crt = 0;

    while(1) 
    {
        nread = read(filedesc1, buf + crt, sb.st_size);
        if(nread == -1) 
        {
            perror("First file coud not be read!\n");
            return errno;
        }
        if(nread == 0)
            break;
        crt+=nread;
    }
    
    int i;

    for(i = 0; i < crt; ) {
        int cnt = write(filedesc2, buf + i, crt);
        if(cnt== -1) 
        {
            perror("First file could not be written in second file!\n");
            return errno;
        }
        i += cnt;
    }

    return 0;
}
