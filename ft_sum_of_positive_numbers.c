#include <stdarg.h>
#include <stdio.h>

static long	ft_sum_of_positive_numbers(int count, ...)
{
	va_list	list;
	long	result;
	long	temp;

	va_start(list, count);
	result = 0;
	while (count)
	{
		temp = va_arg(list, int);
		if (temp > 0)
			result += temp;
		count--;
	}
	va_end(list);
	return (result);
}

int	main(void)
{
	long	result;

	result = ft_sum_of_positive_numbers(9, 55, -4, 57, -45, 8, 83, -76, 423, -999);
	printf("%ld\n", result);
	return (0);
}
