#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char		*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void	ft_print_ast(t_ast *tree, int index, char *str)
{
	if (!tree || !tree->value)
		return ;

	printf("%s %d =>  [%s]\n", str, index, tree->value);
	index++;
	ft_print_ast(tree->left, index, "left");
	index++;
	ft_print_ast(tree->right, index, "right");
}

void	ft_free_ast(t_ast *tree)
{
	if (!tree)
		return ;

	ft_free_ast(tree->left);
	ft_free_ast(tree->right);
	if (tree->value)
	{
		free(tree->value);
		tree->value = NULL;
	}
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
		free(new->value);
		new->value = NULL;
		return (NULL);
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*ft_build_ast_tree(char **av, int start, int end)
{
	int	i;
	t_ast	*tree;
	
	i = start;
	while (i < end)
	{
		if (strcmp(av[i], "|") == 0)
		{
			tree = ft_creat_new_node("|");
			tree->left = ft_build_ast_tree(av, start, i);
			tree->right = ft_build_ast_tree(av, i + 1, end);
			return (tree);
		}
		i++;
	}
	if (start > end)
		return (NULL);
	return (ft_creat_new_node(av[start]));
}

t_ast	*ft_creat_ast_tree(int ac, char **av)
{
	return (ft_build_ast_tree(av, 1, ac - 1));
}

int	main(int ac, char **av)
{
	t_ast	*tree;

	if (ac < 2)
		return (-1);
	
	tree = ft_creat_ast_tree(ac, av);
	if (!tree)
		return (-1);
	
	ft_print_ast(tree, 0, "root");
	ft_free_ast(tree);

	return (0);
}
