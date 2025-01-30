#include <stdio.h>
#include <stdlib.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast	*ft_ast_new(char *value)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->value = value;
	new->left = NULL;
	new->right = NULL;
}

int	main(int ac, char **av)
{
	t_ast *head;

	if (ac < 4)
		return (1);
	head = NULL;
	head = ft_ast_new(av[2]);
	head->right = ft_ast_new(av[1]);
	head->left = ft_ast_new(av[3]);
	printf("%s\n%s\n%s\n", head->value, head->right->value, head->left->value);
	return (0);
}