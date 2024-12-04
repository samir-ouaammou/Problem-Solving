#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	main(void)
{
	ssize_t	fd;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		printf("Error opening file (%s)\n", strerror(errno));
	
	return (0);
}
