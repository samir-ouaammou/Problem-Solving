#include <stdarg.h>
#include <stdio.h>

void	ft_extract_even_numbers(int count, ...)
{
	va_list	list;
	int		value;

	va_start(list, count);
	while (count > 0)
	{
		value = va_arg(list, int);
		if (value % 2 == 0)
			printf("%d\n", value);
		count--;
	}
	va_end(list);
}

int	main(void)
{
	ft_extract_even_numbers(5, 10, 22, 33, 44, 55);
	return (0);
}