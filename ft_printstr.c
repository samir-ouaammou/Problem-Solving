#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static void	  ft_putstr(const char *str)
{
	write (1, str, ft_strlen(str));
}

static void	ft_print_strings(int count, ...)
{
	va_list	list;
	char	*str;

	va_start(list, count);
	while (count)
	{
		str = va_arg(list, char *);
		if (str)
			ft_putstr(str);
		count--;
	}
	va_end(list);
}

int	main(void)
{
	ft_print_strings(7,   "Hi ", NULL, "I'm ", "Samir ", "\0", "Ouaammou ", ":)\n");
	return (0);
}
