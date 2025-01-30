#include <stdio.h>

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	if (!s2)
		return (NULL);
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
	char result[100];

	if (ac >= 2)
		printf("result:   [%s]\n", ft_strcpy(result, av[1]));
	return (0);
}