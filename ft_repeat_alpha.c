#include <unistd.h>

void    ft_repeat_alpha(char *str)
{
    int i;
    int tmp;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            tmp = str[i];
            while (tmp >= 'a')
            {
                write (1, &str[i], 1);
                tmp--;
            }
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            tmp = str[i];
            while (tmp >= 'A')
            {
                write (1, &str[i], 1);
                tmp--;
            }
        }
        else
            write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

int main(int ac, char **av)
{
    if (ac >= 2)
        ft_repeat_alpha(av[1]);
    return (0);
}