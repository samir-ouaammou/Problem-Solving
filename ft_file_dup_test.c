#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int	main(void)
{
	int fd;

	fd = open("file.txt", O_WRONLY);
	if (fd == -1)
		printf("Error (%s)\n", strerror(errno));
	
	else
	{
		int fd2 = dup(fd);
		write (fd, "13\n", 3);
		write (fd2, "37\n", 3);
	}
	
	return (0);
}
