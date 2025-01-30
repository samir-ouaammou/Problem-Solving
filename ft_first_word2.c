#include <unistd.h>

void	ft_first_word(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while ((str[i]) && (str[i] != ' ' && str[i] != '\t'))
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		ft_first_word(av[1]);
	write(1, "\n", 1);
	return (0);
}
