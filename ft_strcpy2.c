#include <stdio.h>

char	*ft_strcpy(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';

	return (s1);
}

int	main(int ac, char **av)
{
	char	*result;

	if (ac >= 2)
	{
		result = ft_strcpy(av[1], av[2]);
		printf("%s\n", result);
	}

	return (0);
}
