#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ast
{
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

int	ft_word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	*ft_strdup_range(const char *start, const char *end)
{
	int		len;
	char	*word;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	for (int i = 0; i < len; i++)
		word[i] = start[i];
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int			words;
	char		**result;
	int			i;
	const char	*start;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i++] = ft_strdup_range(start, s);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

void	ft_print_ast(t_ast *tree, char *str)
{
	if (!tree || !tree->value)
		return ;
	printf("%s ->   %s\n", str, tree->value);
	ft_print_ast(tree->left, "left");
	ft_print_ast(tree->right, "right");
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

t_ast	*ft_build_ast_tree(char **cmds, int start, int end)
{
	t_ast		*tree;
	int		priority;
	int		i;

	priority = 0;
	while (priority < 3)
	{
		i = end;
		while (i >= start)
		{
			if (priority == 0 && cmds[i] && (!strcmp(cmds[i], "||") || !strcmp(cmds[i], "&&")))
			{
				tree = ft_create_new_node(cmds[i]);
				if (!tree)
					return (NULL);
				tree->left = ft_build_ast_tree(cmds, start, i - 1);
				tree->right = ft_build_ast_tree(cmds, i + 1, end);
				return (tree);
			}
			else if (priority == 1 && cmds[i] && (!strcmp(cmds[i], "|")))
			{
				tree = ft_create_new_node(cmds[i]);
				if (!tree)
					return (NULL);
				tree->left = ft_build_ast_tree(cmds, start, i - 1);
				tree->right = ft_build_ast_tree(cmds, i + 1, end);
				return (tree);
			}
			else if (priority == 2 && cmds[i] && (!strcmp(cmds[i], "<") || !strcmp(cmds[i], ">")
					|| !strcmp(cmds[i], "<<") || !strcmp(cmds[i], ">>")))
			{
				tree = ft_create_new_node(cmds[i]);
				if (!tree)
					return (NULL);
				tree->left = ft_build_ast_tree(cmds, start, i - 1);
				tree->right = ft_build_ast_tree(cmds, i + 1, end);
				return (tree);
			}
			i--;
		}
		priority++;
	}
	if (start <= end)
		return (ft_create_new_node(cmds[start]));
	return (NULL);
}

t_ast	*ft_create_ast_tree(char *input)
{
	char	**cmds;

	if (!input || !input[0])
		return (NULL);

	cmds = ft_split(input, ' ');
	if (!cmds)
		return (NULL);
	return (ft_build_ast_tree(cmds, 0, ft_word_count(input, ' ')));
}

int	main(void)
{
	t_ast	*tree;
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (input && input[0])
		{
			tree = ft_create_ast_tree(input);
			if (!tree)
				return (-1);
			ft_print_ast(tree, "root");
			ft_free_ast(tree);
		}
		free(input);
	}
	return (0);
}
