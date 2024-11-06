#include <stdarg.h>
#include <unistd.h>

void    ft_putchar(char *c)
{
    write (1, c, 1);
}

void    ft_print_character(char *format, ... )
{
    va_list list;
    char    *temp;
    int     i;

    va_start(list, format);
    i = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            if (format[i+1] == 'c')
                ft_putchar(va_arg(list, char *));
        }
        i++;
    }
    va_end(list);
    write (1, "\n", 1);
}

int main(void)
{
    ft_print_character("%c %c %c %c %c", "Sss", "aaa", "mmm", "iii", "rrr");
    return (0);
}