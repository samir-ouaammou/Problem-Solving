#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

static void ft_putchar(char c, int *size)
{
    int temp;

    if (*size == -1)
        return ;
    temp = write(1, &c, 1);
    if (temp == -1)
        *size = -1;
    else
        *size += temp;
}

static void ft_putstr(const char *str, int *size)
{
    if (!str)
    {
        ft_putstr("(null)", size);
        return ;
    }
    while (*str)
    {
        ft_putchar(*str, size);
        str++;
    }
}

static void ft_putnbr(int nbr, int *size)
{
    if (nbr == -2147483648)
    {
        ft_putstr("-2147483648", size);
        return;
    }
    if (nbr > 9)
        ft_putnbr(nbr / 10, size);
    ft_putchar(nbr % 10 + '0', size);
}

static void ft_putuni(unsigned int nbr, int *size)
{
    if (nbr > 9)
        ft_putuni(nbr / 10, size);
    ft_putchar(nbr % 10 + '0', size);
}

static void ft_puthex(unsigned int nbr, char *hex, int *size)
{
    if (nbr > 15)
        ft_puthex(nbr / 16, hex, size);
    ft_putchar(hex[nbr % 16], size);
}

static void ft_putptr(unsigned long nbr, int *size)
{
    if (nbr > 15)
        ft_putptr(nbr / 16, size);
    ft_puthex(nbr % 16 , "0123456789abcdef", size);
}

static void ft_all_print(char c,va_list args, int *size)
{
    if (c == '%')
        ft_putchar('%', size);
    else if (c == 'c')
        ft_putchar(va_arg(args, int), size);
    else if (c == 'd' || c == 'i')
        ft_putnbr(va_arg(args, int), size);
    else if (c == 'u')
        ft_putuni(va_arg(args, unsigned int), size);
    else if (c == 's')
        ft_putstr(va_arg(args, char *), size);
    else if (c == 'x')
        ft_puthex(va_arg(args, unsigned int), "0123456789abcdef", size);
    else if (c == 'X')
        ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF", size);
    else if (c == 'p')
    {
        ft_putstr("0x", size);
        ft_putptr(va_arg(args, unsigned long), size);
    }
}

static int  ft_printf(char *format, ... )
{
    va_list args;
    int     size;
    int     i;

    size = 0;
    if (!format)
        return (size);
    va_start(args, format);
    i = 0;
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1] == '\0')
            return (size);
        else if (format[i] == '%' && format[i + 1] != '\0')
            ft_all_print(format[i++ + 1], args, &size);
        else
            ft_putchar(format[i], &size);
        i++;
    }
    va_end(args);
    return (size);
}

int main (void)
{
    int len1;
    int len2;

    len1 = ft_printf("%% %c %s %d %i %u %x %X %p\n", 'S', "Hello", 1337, 42, 2024, 15, 15, &main);
    len2 = printf("%% %c %s %d %i %u %x %X %p\n", 'S', "Hello", 1337, 42, 2024, 15, 15, &main);

    printf("\n%d\n%d\n", len1, len2);

    return (0);
}