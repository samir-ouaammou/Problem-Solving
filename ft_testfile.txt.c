#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	if (access("file.txt", F_OK) == -1)
		printf("Error file not found (%s)\n", strerror(errno));
	else
	{
		if (access("file.txt", R_OK) == -1)
			printf("Error (%s)\n", strerror(errno));
	}
	return (0);
}
