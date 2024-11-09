#include <stdio.h>
#include <stdarg.h>

static int ft_find_minimum(int count, ...)
{
    va_list list;
    int     result;
    int     temp;

    va_start(list, count);
    result = va_arg(list, int);
    count--;
    while (count)
    {
        temp = va_arg(list, int);
        if (result > temp)
            result = temp;
        count--;
    }
    va_end(list);
    return (result);
}

int main(void)
{
    int result;

    result = ft_find_minimum(5,    44, -99, -5, 88, -37, 83);
    printf("%d\n", result);

    return (0);
}