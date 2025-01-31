#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

void	ft_print_ast(t_ast *tree, int *index, char *str)
{
	if (!tree || !tree->value)
		return ;
	printf("%s %d =>   [%s]\n", str, *index, tree->value);
	(*index)++;
	ft_print_ast(tree->left, index, "LEFT");
	(*index)++;
	ft_print_ast(tree->right, index, "RIGHT");
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

t_ast	*ft_create_new_node(char *str)
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

t_ast	*ft_build_ast_tree(char **tokens, int start, int end)
{
	t_ast		*node;
	int		priority;
	int		i;

	priority = 0;
	while (priority < 3)
	{

		i = end;
		while (i >= start)
		{
			if (priority == 0 && (!strcmp(tokens[i], "||") || !strcmp(tokens[i], "&&")))
			{
				node = ft_create_new_node(tokens[i]);
				node->left = ft_build_ast_tree(tokens, start, i - 1);
				node->right = ft_build_ast_tree(tokens, i + 1, end);
				return (node);
			}
			if (priority == 1 && !strcmp(tokens[i], "|"))
			{
				node = ft_create_new_node(tokens[i]);
				node->left = ft_build_ast_tree(tokens, start, i - 1);
				node->right = ft_build_ast_tree(tokens, i + 1, end);
				return (node);
			}
			if (priority == 2 && (!strcmp(tokens[i], "<") || !strcmp(tokens[i], ">")
				|| !strcmp(tokens[i], "<<") || !strcmp(tokens[i], ">>")))
			{
				node = ft_create_new_node(tokens[i]);
				node->left = ft_build_ast_tree(tokens, start, i - 1);
				node->right = ft_build_ast_tree(tokens, i + 1, end);
				return (node);
			}
			i--;
		}
		priority++;
	}
	if (start <= end)
		return (ft_create_new_node(tokens[start]));
	return (NULL);
}

t_ast	*ft_create_ast_tree(int ac, char **av)
{
	return (ft_build_ast_tree(av, 1, ac - 1));
}

int	main(int ac, char **av)
{
	t_ast	*tree;
	int	index;

	if (ac < 2)
		return (2);
	tree = ft_create_ast_tree(ac, av);
	if (!tree)
		return (-1);
	index = 0;
	ft_print_ast(tree, &index, "ROOT");
	ft_free_ast(tree);
	return (0);
}
