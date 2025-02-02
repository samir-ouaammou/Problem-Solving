#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

void	ft_print_ast(t_ast *tree)
{
	if (!tree || !tree->value)
		return ;
	printf("%s\n", tree->value);
	ft_print_ast(tree->left);
	ft_print_ast(tree->right);
}

void	ft_free_ast(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->value)
	{
		free(tree->value);
		tree->value = NULL;
	}
	ft_free_ast(tree->left);
	ft_free_ast(tree->right);
	free(tree);
	tree = NULL;
}

t_ast	*ft_creat_new_node(char *str)
{
	t_ast	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->value = strdup(str);
	if (!new->value)
	{
		free(new);
		new = NULL;
		return (NULL);
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*ft_creat_left_and_right_node(t_ast *root, char *l_value, char *r_value)
{
	if (!root)
		return (NULL);
	root->left = ft_creat_new_node(l_value);
	root->right = ft_creat_new_node(r_value);
	return (root);
}

int	main(int ac, char **av)
{
	t_ast	*tree;

	if (ac < 4)
		return (-1);
	tree = ft_creat_new_node(av[1]);
	if (!tree)
		return (-1);
	tree = ft_creat_left_and_right_node(tree, av[2], av[3]);
	if (tree)
	{
		ft_print_ast(tree);
		ft_free_ast(tree);
	}
	return (0);
}
