#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int filedesc1 = open(argv[1], O_RDONLY);
    if(filedesc1 == -1) 
    {
        perror("First file could not be opened!\n");
        return errno;
    }
    int filedesc2 = open(argv[2], O_WRONLY | O_APPEND | O_CREAT);
    if(filedesc2 == -1)
    {
        perror("Second file could not be opened!\n");
        return errno;
    }
    
    char *buff, *buf;  
    int nread, crt = 0;

	printf("Before while reading\n");

    while(1) 
    {
		printf("Before read\n");
        nread = read(filedesc1, buf, 1);
		printf("After read (nread = %d)\nComparing nread to -1...", nread);
        if(nread == -1) 
        {
            perror("First file coud not be read!\n");
            return errno;
        }
		printf("Comparing nread to 0...");
        if(nread == 0)
            break;

		printf("Trying to read char #%d...", crt + 1);
        *(buff + crt) = *buf;
		printf("Read successfull(?): %c", (char) *buf);
        crt++;
    }

    for(int i = 0; i < crt; ) {
        int cnt = write(filedesc2, *(buff + i), crt);
        if(cnt== -1) 
        {
            perror("First file could not be written in second file!\n");
            return errno;
        }
        i += cnt;
    }

    return 0;
}
