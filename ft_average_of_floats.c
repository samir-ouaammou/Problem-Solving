#include <stdio.h>
#include <stdarg.h>

int    ft_average_of_floats(int count, ... )
{
    va_list			list;
    long			result;
    int				temp;

    va_start(list, count);
    result = 0;
    temp = count;
    while (count)
    {
        result += va_arg(list, int);
        count--;
    }
    va_end(list);
    return (result / temp);
}

int     main()
{
    int    result;
    
    result = ft_average_of_floats(9, 11, 22, 33, 44, 55, 66, 77, 88, 99);
    printf("%d\n", result);
    return (0);
}
