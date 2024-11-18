#include <stdlib.h>
#include <stdio.h>

void	ft_swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int main(int ac, char **av)
{
    if (ac >= 3)
    {
        int n1 = atoi(av[1]);
        int n2 = atoi(av[2]);
        ft_swap(&n1, &n2);
        printf("n1 = [%d]\nn2 = [%d]\n", n1, n2);
    }
    return (0);
}