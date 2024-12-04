#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		av = &av[1];
		execve("/bin/ls", av, NULL);
	}
	
	return (0);
}
