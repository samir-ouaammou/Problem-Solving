#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int	main(void)
{
	int fd = open("file.txt", O_WRONLY);
	if (fd == -1)
		printf("Error (%s)\n", strerror(errno));
	else
	{
		if (dup2(fd, 1) == -1)
			perror("Error");
		else
			write (1, "1337\n", 5);
	}

	return (0);
}
