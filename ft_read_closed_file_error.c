#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	main(void)
{
	ssize_t	fd;
	ssize_t	len;
	char	temp[1337];

	fd = open("file.txt", O_CREAT, O_RDONLY);
	if (fd == -1)
		printf("Error opening file (%s)\n", strerror(errno));
	else
	{
		close(fd);
		len = read(fd, temp, 1337);
		printf("Error reading file (%s)\n", strerror(errno));
	}

	return (0);
}
