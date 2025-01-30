#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char	*argv[];

	argv[] = {"ls", NULL};
	execve("/bin/ls", argv, NULL);
	return (0);
}
