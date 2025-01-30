#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t p1, p2;
	p2 = getpid();
	printf("main pid: (%d)\n", p2);
	p1 = fork();
	if (p1 < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		return (0);
	}
	if (p1 > 0)
		printf("Parant pid: (%d)\n", getpid());
	if (p1 == 0)
		printf("Child pid: (%d)\n", getpid());
	return (0);
}
