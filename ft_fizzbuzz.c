#include <unistd.h>

static void ft_putchar(char c)
{
    write (1, &c, 1);
}

static void ft_putstr(char *str)
{
    while (*str)
    {
        ft_putchar(*str);
        str++;
    }
}

static void ft_putnbr(int nbr)
{
    if (nbr > 9)
        ft_putnbr(nbr / 10);
    ft_putchar(nbr % 10 + '0');
}

static void  ft_fizzbuzz(void)
{
    int index;

    index = 1;
    while (index <= 100)
    {
        if (index % 3 == 0 && index % 5 == 0)
            ft_putstr("fizzbuzz\n");
        else if (index % 3 == 0)
            ft_putstr("fizz\n");
        else if (index % 5 == 0)
            ft_putstr("buzz\n");
        else
        {
            ft_putnbr(index);
            ft_putchar('\n');
        }
        index++;
    }
}

int main(void)
{
    ft_fizzbuzz();

    return (0);
}