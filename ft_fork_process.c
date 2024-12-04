#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

int	main(void)
{
	printf("Hello ");

	pid_t	pids;

	pids = fork();

	if (pids < 0)
	{
		perror("Error");
		return (0);
	}
	if (pids == 0)
	{
		printf("code fork\n");
		printf("pid fork => %d\n", getpid());
	}
	if (pids > 0)
	{
		printf("code main\n");
		printf("pid main => %d\n", getpid());
	}
	
	return (0);
}
