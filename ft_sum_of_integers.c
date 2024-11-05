#include <stdarg.h>
#include <stdio.h>

int	ft_sum_of_integers(int count, ...)
{
	va_list	list;
	int		result;

	va_start(list, count);
	result = 0;
	while (count)
	{
		result += va_arg(list, int);
		count--;
	}
	va_end(list);
	return (result);
}

int	main(void)
{
	int	result;

	result = ft_sum_of_integers(5, 11, 22, 33, 44, 55);
	printf("%d\n", result);
	return (0);
}
