#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int	main(void)
{
	int fd = open("file.txt", O_RDONLY);

	if (fd == -1)
		perror("Error opening file");

	return (0);
}
