#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


int	main(int ac, char **av)
{
	if (ac < 0)
		return (0);
	
	char	*str = av[1];
	av = &av[2];
	execve(str, av, NULL);

	return (0);
}
