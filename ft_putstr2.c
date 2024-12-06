#include <unistd.h>

void	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write (1, &tr[i], 1);
		i++;
	}
}
