#include <stdio.h>
#include <stdarg.h>

void    ft_print_strings(int count, ... )
{
    va_list        list;

    va_start(list, count);
    while (count)
    {
        printf("%s\n", va_arg(list, char *));
        count--;
    }
    va_end(list);
}

int    main(int ac, char **av)
{
    if (ac >= 5)
        ft_print_strings(ac-1,    av[1], av[2], av[3], av[5]);

    return (0);
}
