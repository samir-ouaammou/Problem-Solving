#include <stdio.h>
#include <stdarg.h>

static int   ft_sum_positive_numbers(int count, ...)
{
    va_list list;
    int     result;
    int     temp;

    va_start(list, count);
    result = 0;
    while (count)
    {
        temp = va_arg(list, int);
        if (temp > 0)
            result += temp;
        count--;
    }
    va_end(list);
    return (result);
}


int main(void)
{
    int result;

    result = ft_sum_positive_numbers(5,     -4, 88, 66, -33, 77);
    printf("%d\n", result);

    return (0);
}