#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{	
	char shm_name[] = "myshm";
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(shm_fd < 0)
	{
		perror(NULL);
		return errno;
	}

	int nrNumbers = argc - 1;
	int pageSize = getpagesize();
	size_t shm_size = pageSize * nrNumbers;
	if(ftruncate(shm_fd, shm_size) == -1)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}

	int i, pid;
	printf("Starting parent %d\n", getpid());
	for(i = 1; i <= argc - 1 ; ++i)
	{
		int pid = fork();

		if(pid < 0)
		{
			return errno;
		}
		else if(pid == 0)
		{
			int * shm_ptr = mmap(0, pageSize, PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*pageSize); //
			if(shm_ptr == MAP_FAILED)
			{
				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}

			int n;
			sscanf(argv[i], "%d", &n);

			//printf("%d: %d ", n, n);
			*shm_ptr = n;
			shm_ptr++;
			while(n != 1)
			{
				if(n%2)
				{
					n = 3*n + 1;
					*shm_ptr = n;
					shm_ptr++;
					//printf("%d ", n);
				}
				else
				{
					n = n/2;
					*shm_ptr = n;
					shm_ptr++;
					//printf("%d ", n);
				}
			}
			//printf(".\n");
			*shm_ptr = NULL;
			
			printf("Done Parent %d Me %d\n", getppid(), getpid());

			munmap(shm_ptr, pageSize);

			return 0;
		}
	}

	while(wait(NULL) != -1) { }

	for(i = 1 ; i <= argc - 1 ; ++i)
	{
		int * shm_ptr = mmap(0, pageSize, PROT_READ, MAP_SHARED, shm_fd, (i-1)*pageSize);
		
		printf("%s: ", argv[i]);
		while(*shm_ptr != 0)
		{
			printf("%d ", *shm_ptr);
			shm_ptr++;
		}
		printf("\n");

		munmap(shm_ptr, pageSize);
		
	}

	printf("Done Parent %d Me %d\n", getppid(), getpid());

	shm_unlink(shm_name);

	return 0;
}