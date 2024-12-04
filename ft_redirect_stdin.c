#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int	main(void)
{
	int fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		printf("Error (%s)\n", strerror(errno));
	else
	{
		char buffer[1337];

		if (dup2(fd, 0) == -1)
			perror ("Error");
		else
		{
			read (0, buffer, 1337);
			printf("buffer ==> %s\", buffer);
		}
	}

	return (0);
}
