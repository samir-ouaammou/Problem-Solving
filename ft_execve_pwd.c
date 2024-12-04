#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac >= 2)
		execve("/bin/pwd", &av[1], NULL);

	return (0);
}
