#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int	main(int ac, char **av)
{
	int	fd[2];
	char	buffer[1337];
	ssize_t	len;
	ssize_t	temp;
	int	ps;

	if (ac < 2)
		return (0);
	len = 0;
	ps = pipe(fd);
	if (ps < 0)
	{
		perror("Error");
		exit(0);
	}
	
	len = write (fd[1], av[1], strlen(av[1]));
	if (len < 0)
	{
		perror("Error");
		exit(0);
	}
	len = read(fd[0], buffer, sizeof(buffer));
	if (len < 0)
	{
		perror("Error");
		exit(0);
	}
	buffer[len] = '\0';
	printf("Result = (%s)\n", buffer);
	
	close(fd[1]);
	close(fd[0]);

	return (0);
}

