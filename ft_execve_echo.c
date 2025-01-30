#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac > 2)
		execve("/bin/echo", &av[1], NULL);
	return (0);
}
