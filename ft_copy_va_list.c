#include <stdarg.h>
#include <stdio.h>

void	ft_copy_va_list(int c, ...)
{
	va_list	list;
	va_list	clist;

	va_start(list, c);
	va_copy(clist, list);
    
	while (c)
	{
		printf("%d\n", va_arg(clist, int));
		c--;
	}
	va_end(list);
	va_end(clist);
}

int	main(void)
{
	ft_copy_va_list(9, 11, 22, 33, 44, 55, 66, 77, 88, 99);
	return (0);
}