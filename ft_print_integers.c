#include <stdarg.h>
#include <stdio.h>

static void	ft_print_numbers(int count, ...)
{
	va_list	list;

	va_start(list, count);
	while (count > 0)
	{
		count--;
		printf("%d\n", va_arg(list, int));
	}
	va_end(list);
}

int	main(void)
{
	ft_print_numbers(9, 1, 22, 333, 4444, 55555, 666666, 7777777, 88888888,
		999999999);
	return (0);
}
