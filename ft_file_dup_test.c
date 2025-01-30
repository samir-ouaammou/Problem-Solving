#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int	fd;
	int	fd2;

	fd = open("file.txt", O_WRONLY);
	if (fd == -1)
		printf("Error (%s)\n", strerror(errno));
	else
	{
		fd2 = dup(fd);
		write(fd, "13\n", 3);
		write(fd2, "37\n", 3);
	}
	return (0);
}
