#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int	fd = open ("file.txt", O_WRONLY);
	if (fd == -1)
		perror("Error");
	pid_t	ps;
	printf("1\n");
	ps = fork();
	if (ps < 0)
	{
		perror("Error");
		exit(1);
	}
	if (ps == 0)
	{
		write (fd, "1337\n", 5);
		printf("number process chelde:  %d\n", getpid());
	}
	else
	if (ps > 0)
	{
		wait(NULL);
		write (fd, "42\n", 5);
		printf("number process futher:  %d\n", getpid());
	}
	return (0);
}

