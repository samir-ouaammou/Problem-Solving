#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		printf("path => %s\n", path);
	else
		printf("no path");
	return (0);
}
