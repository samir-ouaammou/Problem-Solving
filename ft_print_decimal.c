#include <stdarg.h>
#include <unistd.h>

void    ft_putnbr(int nbr)
{
    char    c;

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

void    ft_print_decimal(char *format, ... )
{
    va_list list;
    int     i;

    va_start(list, format);
    i = 0;
    while (format[i])
    {
        if (format[i] == '%')
            ft_putnbr(va_arg(list, int));
        i++;
    }
    write (1, "\n", 1);
    va_end(list);
}

int main(void)
{
    ft_print_decimal("%d %d %d %d", 1, 3, 3, 7);
    return (0);
}