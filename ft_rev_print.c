#include <unistd.h>

void	ft_rev_print(char *str)
{
	int	i;

	if (!str)
		return ;
	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		write(1, &str[i], 1);
	}
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		ft_rev_print(av[1]);
	write(1, "\n", 1);
	return (0);
}