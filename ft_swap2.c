#include <stdio.h>
#include <stdlib.h>

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}


int	main(int ac, char **av)
{
	int a = atoi(av[1]);
	int b = atoi(av[2]);

	ft_swap(&a, &b);
	printf("a = %d\nb = %d\n", a, b);

	return (0);
}
