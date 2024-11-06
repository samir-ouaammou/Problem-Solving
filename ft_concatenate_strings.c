#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

static size_t  ft_strlen (const char *str)
{
    size_t  index;

    index = 0;
    while (str[index])
        index++;
    return (index);
}

static void    ft_putstr(char *str)
{
    if (str)
        write (1, str, ft_strlen(str));
}

static void    ft_concatenate_strings(int count, ... )
{
    va_list list;

    va_start(list, count);
    while (count > 1)
    {
        ft_putstr(va_arg(list, char *));
        count--;
    }
    va_end(list);
}

int main(void)
{
    ft_concatenate_strings(5,   "Hi ", "I'm ", "Samir " "Ouaammou ", ":)\n");

    return (0);
}