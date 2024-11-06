#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static	void	ft_putnbr(int nbr)
{
	char c;
	if (nbr == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		write (1, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = nbr % 10 + '0';
	write (1, &c, 1);
}

static void	ft_print_numbers(int count, ...)
{
	va_list	list;
	int		temp;

	va_start(list, count);
	while (count > 0)
	{
		temp = va_arg(list, int);
		ft_putnbr(temp);
		write (1, "\n", 1);
		count--;
	}
	va_end(list);
}

int	main(void)
{
	ft_print_numbers(9, 1, 22, 333, 4444, 55555, 666666, 7777777, 2147483647, -2147483648);
	return (0);
}
