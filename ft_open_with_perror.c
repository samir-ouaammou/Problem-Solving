#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (0);
}
