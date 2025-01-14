#include <stdarg.h>
#include <unistd.h>

void    ft_putunsigned(unsigned int n)
{
    char    c;

    if (n < 0)
        return ;
    if (n > 9)
        ft_putunsigned(n / 10);
    c = n % 10 + '0';
    write (1, &c, 1);
}

void    ft_print_unsigned(char *format, ... )
{
    va_list list;
    int     i;

    va_start(list, format);
    i = 0;
    while (format[i])
    {
        if (format[i] == '%')
            ft_putunsigned(va_arg(list, unsigned int));
        i++;
    }
    write (1, "\n", 1);
    va_end(list);
}

int   main(void)
{
    ft_print_unsigned("%u %u %u %u", 1, 3, 3, 7);
    return (0);
}
