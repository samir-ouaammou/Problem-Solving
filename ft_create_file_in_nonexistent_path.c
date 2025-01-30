#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	ssize_t	fd;

	fd = open("/nonexistent_folder/file.txt", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	else
		printf("file opened successfully\n");
	return (0);
}
