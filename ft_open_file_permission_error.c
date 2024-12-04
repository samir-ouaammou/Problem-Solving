#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int	main(void)
{
	ssize_t	fd;

	fd = open("/root/file.txt", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	else
		printf("file opened successfully.\n");

	return (0);
}
