#include <unistd.h>

void    ft_ret_13(char *str)
{
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'm' || str[i] >= 'A' && str[i] <= 'M')
            str[i] = str[i] + 13;
        else if (str[i] > 'm' && str[i] <= 'z' || str[i] > 'M' && str[i] <= 'Z')
            str[i] = str[i] - 13;
        write(1, &str[i], 1);
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac >= 2)
        ft_ret_13(av[1]);
    write(1, "\n", 1);
    return (0);
}