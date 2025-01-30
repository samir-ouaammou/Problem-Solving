#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pids;

	printf("Hello ");
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
