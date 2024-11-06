#include <stdarg.h>
#include <stdio.h>

static int	ft_min_of_numbers(int count, ...)
{
	va_list	list;
	int		result;
	int		temp;

	va_start(list, count);
	result = va_arg(list, int);
	while (count > 1)
	{
		temp = va_arg(list, int);
		if (result > temp)
			result = temp;
		count--;
	}
	va_end(list);
	return (result);
}

int	main(void)
{
	int	result;

	result = ft_min_of_numbers(9, 81, 65, 328, -999, 751, -34, -87, -1234, -995);
	printf("%d\n", result);
	return (0);
}
