#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	char	*str;

	if (ac < 2)
		return (0);


	str = av[1];
	av = &av[2];

	execve(str, av, NULL);

	return (0);
}
