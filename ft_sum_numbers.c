#include <stdarg.h>
#include <stdio.h>

static int	ft_sum_numbers(int count, ...)
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
	int result;

	result = ft_sum_numbers(5, 99, 11, 88, 22, 55);
	printf("%d\n", result);

	return (0);
}