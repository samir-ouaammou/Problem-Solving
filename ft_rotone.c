#include <unistd.h>

void	ft_rotone(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == 'z' || str[i] == 'Z')
			str[i] = str[i] - 25;
		else if ((str[i] >= 'a' && str[i] <= 'y') || (str[i] >= 'A'
					&& str[i] < 'Y'))
			str[i] = str[i] + 1;
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		ft_rotone(av[1]);
	write(1, "\n", 1);
	return (0);
}