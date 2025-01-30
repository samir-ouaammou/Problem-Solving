#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		printf("%d", ft_strlen(av[1]));
	}
	return (0);
}
