#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	if (unlink("file.txt") == -1)
		perror("Error opening file");
	else
		printf("file deleted successfully.\n");
	return (0);
}
