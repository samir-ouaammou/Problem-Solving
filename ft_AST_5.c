#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

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

t_ast	*ft_build_tree(char **av, int *start, int end)
{
	t_ast	*tree;

	if (*start > end)
		return (NULL);
	tree = ft_creat_new_node(av[*start]);
	(*start)++;
	tree->left = ft_build_tree(av, start, end);
	(*start)++;
	tree->right = ft_build_tree(av, start, end);
	return (tree);
}

t_ast	*ft_creat_ast_tree(int ac, char **av)
{
	int	start;

	start = 1;
	return (ft_build_tree(av, &start, ac - 1));
}

int	main(int ac, char **av)
{
	t_ast	*tree;

	if (ac < 2)
		return (-1);
	tree = ft_creat_ast_tree(ac, av);
	if (tree)
	{
		ft_print_ast(tree);
		ft_free_ast(tree);
	}
	return (0);
}
