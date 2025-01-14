#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	char	*argv[] = {"ls", NULL};
	execve("/bin/ls", argv, NULL);

	return (0);
}

