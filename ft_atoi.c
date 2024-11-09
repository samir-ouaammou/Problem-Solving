#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_atoi(const char *str)
{
	long	res;
	size_t	i;
	int		sgn;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
		
	sgn = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}

	res = 0;
	while (str[i] && (str[i]) >= '0' && str[i] <= '9')
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
			return (-sgn * (sgn == 1));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sgn);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		printf("\natoi in c:   %d\nMy atoi:   %d\n\n", atoi(av[1]),
			ft_atoi(av[1]));
	return (0);
}