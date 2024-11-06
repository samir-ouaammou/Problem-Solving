#include <stdarg.h>
#include <unistd.h>

size_t  ft_strlen(const char *str)
{
    size_t  index;

    index = 0;
    while (str[index])
        index++;
    return (index);
}

void ft_putstr(const char *str)
{
    write (1, str, ft_strlen(str));
}

void    ft_print_string(char *format, ... )
{
    va_list list;
    int     i;
    
    va_start(list, format);
    i = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            ft_putstr(va_arg(list, char *));
            write (1, "\n", 1);
        }
        i++;
    }
    va_end(list);
}

int main(void)
{
    ft_print_string("%s %s %s %s", "Hi", "Im", "Smir", "Ouaammou");
    return (0);
}