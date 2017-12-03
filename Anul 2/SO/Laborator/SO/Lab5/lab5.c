#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>

int main(int argc, char **argv) {
    char *shm_name = "myshm";
    int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

    if (shm_fd == -1) {
        perror(NULL);
        return errno;
    }

    int page_size = getpagesize();
    int length = page_size * (argc - 1);
    if (ftruncate(shm_fd, length)) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int i;
    printf("Starting parent %d\n", getpid());
    for (i = 1; i < argc; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror(NULL);
            shm_unlink(shm_name);
            return errno;
        } else if (!pid) {
            void *shm_ptr = mmap(0, page_size, PROT_WRITE, 
                                        MAP_SHARED, shm_fd, page_size * (i - 1));
            if (shm_ptr == MAP_FAILED) {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }

            int n = atoi(argv[i]);

            int index = sprintf(shm_ptr, "%d: ", n);
            while (n != 1)
            {
                index += sprintf(shm_ptr + index, "%d ", n);
                
                if (n % 2) {
                    n = 3 * n + 1;
                } else {
                    n /= 2;
                }
            }            
            sprintf(shm_ptr + index, "%d.\n", n);

            // printf(shm_ptr);

            printf("Done Parent %d Me %d\n", getppid(), getpid());

            munmap(shm_ptr, page_size);

            return 0;            
        }
    }

    for (i = 1; i < argc; ++i) {
        wait(NULL);
    }

    for (i = 1; i < argc; ++i) {
        void *shm_ptr = mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, page_size * (i - 1));   
        if (shm_ptr == MAP_FAILED) {
            perror(NULL);
            shm_unlink(shm_name);
            return errno;
        }

        printf(shm_ptr);
        munmap(shm_ptr, page_size);         
    }

    shm_unlink(shm_name);

    return 0;
}
