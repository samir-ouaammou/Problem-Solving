#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	fd = open("file.txt", O_WRONLY);
	if (fd < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	if (dup2(fd, 1) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	printf("Hello Samir\n");
	write(1, "1337\n", 5);
	return (0);
}
