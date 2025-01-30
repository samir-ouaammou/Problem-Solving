#include <stdarg.h>
#include <unistd.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_print_characters(int count, ...)
{
	va_list	list;
	char	*temp;

	va_start(list, count);
	while (count > 1)
	{
		temp = va_arg(list, char *);
		if (temp)
		{
			while (*temp)
			{
				ft_putchar(*temp);
				temp++;
			}
		}
		count--;
	}
	va_end(list);
}

int	main(void)
{
	ft_print_characters(55, "Hi ", "I'm ", "Samir "
											"Ouaammou ",
						":)\n");
	return (0);
}
