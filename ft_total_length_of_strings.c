#include <stdio.h>
#include <stdarg.h>

static int  ft_strlen(const char *str)
{
    size_t  index;

    index = 0;
    while (str[index])
        index++;
    
    return (index);
}

int ft_total_length_of_strings(int count, ... )
{
    va_list list;
    int     result;

    va_start(list, count);
    result = 0;
    while (count > 1)
    {
        result += ft_strlen(va_arg(list, char *));
        count--;
    }
    va_end(list);
    return (result);
}

int main(void)
{
    int result;

    result = ft_total_length_of_strings(5,   "Hi ", "I'm ", "Samir " "Ouaammou ", ":)\n");
    printf("%d\n", result);

    return (0);
}