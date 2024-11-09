#include <unistd.h>

static int  ft_check(char c)
{
    if ((c == ' ') || (c == '\t') || (c == '\n'))
        return (1);
    
    return (0);
}

static void ft_first_word(char *str)
{
    int index;

    if (!str)
        return ;
        
    index = 0;
    // Skip any leading whitespace
    while ((str[index]) && (ft_check(str[index])))
        index++;
        
    // Print characters until whitespace is encountered
    while ((str[index]) && (!ft_check(str[index])))  
    {
        write(1, &str[index], 1);
        index++;
    }
}

int main(int ac, char **av)
{
    if (ac >= 2)
    {
        ft_first_word(av[1]);
        write(1, "\n", 1);
    }
    
    return (0);
}
