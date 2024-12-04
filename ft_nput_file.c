#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	int  fdf = open("file.txt", O_WRONLY);
	if (fdf == -1)
	{
		perror("Error opening file");
		return (0);
	}
	
	int fd = dup(1);
	//printf("fd: %d\n", fd);
	//printf("fdf: %d\n", fdf);
	dup2(fdf, fd);
	//printf("Hi si samir");
	write(fd, "heyy", 4);
	return (0);
}

