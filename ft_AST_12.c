#include <readline/history.h>
#include <readline/readline.h>
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
	if (!tree || !tree->value || !tree->value[0])
		return ;
	printf("%s =>   %s\n", str, tree->value);
	ft_print_ast(tree->left, "left");
	ft_print_ast(tree->right, "right");
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
	t_ast	*tree;
	int		i;
	int		parent;
	int		brackets;
	int		priority;

	if (start > end || !tokens)
		return (NULL);
	if (tokens[start][0] == '(' && tokens[end][0])
	{
		brackets = 1;
		i = start + 1;
		while (tokens[i] && i < end)
		{
			if (tokens[i][0] == '(')
				brackets++;
			else if (tokens[i][0] == ')')
				brackets--;
			if (brackets == 0)
				break ;
			i++;
		}
		if (brackets == 1)
			return (ft_build_ast_tree(tokens, start + 1, end - 1));
	}
	parent = 0;
	priority = 0;
	while (priority < 3)
	{
		i = end;
		while (i >= start)
		{
			if (tokens[i][0] == ')')
				parent++;
			else if (tokens[i][0] == '(')
				parent--;
			if (parent == 0)
			{
				if (priority == 0 && (!strcmp(tokens[i], "||")
						|| !strcmp(tokens[i], "&&")))
				{
					tree = ft_create_new_node(tokens[i]);
					if (!tree)
						return (NULL);
					tree->left = ft_build_ast_tree(tokens, start, i - 1);
					tree->right = ft_build_ast_tree(tokens, i + 1, end);
					return (tree);
				}
				if (priority == 1 && !strcmp(tokens[i], "|"))
				{
					tree = ft_create_new_node(tokens[i]);
					if (!tree)
						return (NULL);
					tree->left = ft_build_ast_tree(tokens, start, i - 1);
					tree->right = ft_build_ast_tree(tokens, i + 1, end);
					return (tree);
				}
				if (priority == 2 && (!strcmp(tokens[i], "<")
						|| !strcmp(tokens[i], ">") || !strcmp(tokens[i], "<<")
						|| !strcmp(tokens[i], ">>")))
				{
					tree = ft_create_new_node(tokens[i]);
					if (!tree)
						return (NULL);
					tree->left = ft_build_ast_tree(tokens, start, i - 1);
					tree->right = ft_build_ast_tree(tokens, i + 1, end);
					return (tree);
				}
			}
			i--;
		}
		priority++;
	}
	if (start <= end)
		return (ft_create_new_node(tokens[start]));
	return (NULL);
}

t_ast	*ft_create_ast_tree(char *input)
{
	char	**cmds;

	if (!input)
		return (NULL);
	cmds = ft_split(input, ' ');
	if (!cmds)
		return (NULL);
	return (ft_build_ast_tree(cmds, 0, ft_word_count(input, ' ') - 1));
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
				printf("Don't creat ast tree\n");
			if (tree)
			{
				ft_print_ast(tree, "root");
				ft_free_ast(tree);
			}
			add_history(input);
			free(input);
		}
	}
	return (0);
}
