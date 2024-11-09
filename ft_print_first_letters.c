#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

static void   ft_putchar(char c)
{
    write (1, &c, 1);
}

static void ft_print_first_letters(int count, ... )
{
    va_list list;
    char    *temp;

    va_start(list, count);
    while (count)
    {
        temp = va_arg(list, char *);
        if (temp)
            if (temp[0] != '\0')
                ft_putchar(temp[0]);
        count--;
    }
    va_end(list);
}

int main(void)
{
    ft_print_first_letters(11,   "Sss", NULL, "ahf", "\0hi", "mbf", "ibk", "rkl", " 42", ":ksb", ")jb", "\n1337");

    return (0);
}