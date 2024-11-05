#include <stdio.h>
#include <stdarg.h>

float ft_average_of_floats_2(int count, ...)
{
    va_list		list;
    float		result;

    va_start(list, count);
    result = 0;
    while (count)
    {
        result += va_arg(list, double);;
        count--;
    }
    va_end(list);
    return(result / count);
}

int main(void)
{
    float result;

	result = ft_average_of_floats_2(5, 5.0, 47.0, 6.0, 8.0, 99.0);
    printf("%f\n", result);
    
    return 0;
}
