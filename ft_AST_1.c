#include <stdio.h>
#include <stdlib.h>

typedef struct s_ast
{
    char            *value;
    struct s_ast    *left;
    struct s_ast    *right;
}   t_ast;

t_ast   *ft_ast_new(char *countent)
{
    t_ast   *new;

    new = malloc(sizeof(t_ast));
    if (!new)
        return (NULL);
    new->value = countent;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

int    main(int ac, char **av)
{
    t_ast   *head;

    if (ac < 3)
        return (0);
    head = ft_ast_new(av[1]);
    head->right = ft_ast_new(av[2]);
    printf("%s\n%s\n",head->value, head->right->value);
    free(head->right);
    head->right = NULL;
    free(head);
    head = NULL;
}