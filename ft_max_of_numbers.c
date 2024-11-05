#include <stdio.h>
#include <stdarg.h>

int    ft_max_of_numbers(int count, ... )
{
    va_list		list;
    int			result;
    int			temp;;

    va_start(list, count);
    result = va_arg(list, int);
    count--;
    while (count)
    {
        temp = va_arg(list, int);
        if (result < temp)
            result = temp;
        count--;
    }
    va_end(list);
    return (result);
}

int     main(void)
{
    int result;

    result = ft_max_of_numbers(9, 123, 32, 231, 251, 351, 462, 999, 731, 91);
    printf("%d\n", result);
    
    return (0);
}
