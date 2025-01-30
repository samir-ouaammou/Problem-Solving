#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_ast	*ft_creat_ast_node(char *str)
{
	t_ast	*new_node;

	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->value = strdup(str);
	if (!new_node->value)
	{
		free(new_node);
		new_node = NULL;
		return (NULL);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
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

t_ast	*ft_biuld_ast_tree(char **strs, int *start, int end)
{
	t_ast	*tree;

	if (*start > end || !strs || !strs[*start])
		return (NULL);
	tree = ft_creat_ast_node(strs[*start]);
	if (!tree)
		return (NULL);
	(*start)++;
	tree->left = ft_biuld_ast_tree(strs, start, end);
	(*start)++;
	tree->right = ft_biuld_ast_tree(strs, start, end);
	return (tree);
}

t_ast	*ft_creat_ast(int ac, char **av)
{
	int	i;

	i = 1;
	return (ft_biuld_ast_tree(av, &i, ac - 1));
}

int	main(int ac, char **av)
{
	t_ast	*tree;

	if (ac < 2)
		return (-1);
	tree = ft_creat_ast(ac, av);
	if (!tree)
		return (-1);
	ft_print_ast(tree);
	ft_free_ast(tree);
	return (0);
}
