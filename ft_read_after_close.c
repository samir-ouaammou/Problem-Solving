#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	ssize_t	fd;
	ssize_t	len;
	char	temp[1337];

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	else
	{
		close(fd);
		len = read(fd, temp, 1337);
		if (len == -1)
			perror("Error reading file");
	}
	return (0);
}
