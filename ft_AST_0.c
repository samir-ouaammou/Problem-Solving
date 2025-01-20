#include <stdio.h>
#include <stdlib.h>

typedef struct s_ast
{
    char        *value;
    struct s_ast    *left;
    struct s_ast    *right;
}   t_ast;

t_ast   *ft_ast_new(char *value)
{
    t_ast   *new;

    new = malloc(sizeof(t_ast));
    if (!new)
        return (NULL);
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

int main(void)
{
    t_ast   *head;

    head = ft_ast_new("1337");
    printf("%s\n", head->value);
    free(head);
    head = NULL;
    return (0);
}