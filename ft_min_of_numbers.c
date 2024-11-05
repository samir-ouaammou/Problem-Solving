#include <stdio.h>
#include <stdarg.h>

int	ft_min_of_numbers(int count, ... )
{
	va_list		list;
	int			result;
	int			temp;

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

	result = ft_min_of_numbers(9,	81, 65, 328, -1337, 751, -34, -87, -1234, -999);
	printf("%d\n", result);	

	return (0);
}
