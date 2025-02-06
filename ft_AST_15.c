#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list
{
	char			**value;
	struct s_list	*next;
}					t_list;

typedef struct s_ast
{
	char			**value;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_parsing
{
	int				i;
	int				j;
	int				bol;
	int				len;
	int				free;
	int				parent;
	int				brackets;
	int				priority;
	char			chr;
	char			*cmds;
	char			*input;
	char			**temp;
	t_ast			*three;
	t_list			*tokens;
	t_list			*lst_help1;
	t_list			*lst_help2;
	t_list			*start_node;
	t_list			*end_node;
}					t_parsing;

void	ft_init_parsing(t_parsing *shell)
{
	shell->i = 0;
	shell->j = 0;
	shell->len = 0;
	shell->bol = 0;
	shell->free = 0;
	shell->brackets = 0;
	shell->cmds = NULL;
	shell->temp = NULL;
	shell->three = NULL;
	shell->tokens = NULL;
	shell->lst_help1 = NULL;
	shell->lst_help2 = NULL;
}

void	ft_free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->value)
	{
		i = 0;
		while (node->value[i])
		{
			free(node->value[i]);
			node->value[i] = NULL;
			i++;
		}
		free(node->value);
		node->value = NULL;
	}
	ft_free_ast(node->left);
	ft_free_ast(node->right);
	free(node);
	node = NULL;
}

void	ft_free_tokens(t_parsing *shell)
{
	if (!shell || !shell->tokens)
		return ;
	while (shell->tokens)
	{
		shell->i = 0;
		if (shell->tokens->value)
		{
			while (shell->tokens->value[shell->i])
			{
				free(shell->tokens->value[shell->i]);
				shell->tokens->value[shell->i] = NULL;
				shell->i++;
			}
			free(shell->tokens->value);
			shell->tokens->value = NULL;
		}
		shell->lst_help1 = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(shell->lst_help1);
	}
}

void	ft_free_args(t_parsing *shell)
{
	if (!shell || shell->free == -1)
		return ;
	shell->free = -1;
	if (shell->cmds != NULL)
		free(shell->cmds);
	if (shell->temp)
	{
		shell->i = 0;
		while (shell->temp[shell->i])
		{
			if (shell->temp[shell->i] != NULL)
			{
				free(shell->temp[shell->i]);
				shell->temp[shell->i] = NULL;
			}
			shell->i++;
		}
		free(shell->temp);
		shell->temp = NULL;
	}
}

void	ft_free_parsing(t_parsing *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->free != -1)
		ft_free_args(shell);
	if (shell->tokens)
		ft_free_tokens(shell);
	if (shell->three)
		ft_free_ast(shell->three);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		str_len;
	char	*res;

	str_len = ft_strlen(s);
	res = malloc(str_len + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, str_len + 1);
	return (res);
}

char	**free_prev(char **res, int i)
{
	while (i--)
		free(res[i]);
	free(res);
	return (NULL);
}

int	count_word(const char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			word++;
		i++;
	}
	return (word);
}

char	**ft_util(char **res, const char *s, char c, int c_word)
{
	int	i;
	int	j;
	int	e;
	int	len;

	i = 0;
	j = 0;
	while (i < c_word)
	{
		while (s[j] && s[j] == c)
			j++;
		e = j;
		while (s[j] && s[j] != c)
			j++;
		len = j - e;
		res[i] = malloc(len + 1);
		if (!res[i])
			return (free_prev(res, i));
		ft_memcpy(res[i], s + e, len);
		res[i][len] = '\0';
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		c_word;
	char	**res;

	if (!s)
		return (NULL);
	c_word = count_word(s, c);
	res = malloc(sizeof(char *) * (c_word + 1));
	if (res == NULL)
		return (NULL);
	return (ft_util(res, s, c, c_word));
}

int	ft_is_redirections(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "<") || !ft_strcmp(shell->temp[index],
			">") || !ft_strcmp(shell->temp[index], ">>")
		|| !ft_strcmp(shell->temp[index], "<<"))
		return (1);
	return (0);
}

int	ft_is_logical_operators(t_parsing *shell, int index)
{
	if (!shell->temp[index])
		return (0);
	if (!ft_strcmp(shell->temp[index], "|") || !ft_strcmp(shell->temp[index],
			"&") || !ft_strcmp(shell->temp[index], "||")
		|| !ft_strcmp(shell->temp[index], "&&"))
		return (1);
	return (0);
}

void	ft_remainder_of_this_function(t_parsing *shell)
{
	if ((!ft_strcmp(shell->temp[shell->i], "(")
			&& (ft_is_logical_operators(shell, shell->i + 1)))
		|| (!ft_strcmp(shell->temp[shell->i + 1], ")")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i)))
		|| (!ft_strcmp(shell->temp[shell->i], "(")
			&& !ft_strcmp(shell->temp[shell->i + 1], ")"))
		|| (!ft_strcmp(shell->temp[shell->i + 1], "|")
			&& (ft_is_logical_operators(shell, shell->i)
				|| ft_is_redirections(shell, shell->i))))
		ft_free_args(shell);
}

void	ft_check_operator_position(t_parsing *shell)
{
	if (shell->free == -1 || !shell->temp || !shell->temp[0])
		return ;
	shell->i = 0;
	while (shell->temp && shell->temp[shell->i])
	{
		if ((shell->i == 0 && ft_is_logical_operators(shell, 0))
			|| (!shell->temp[shell->i + 1] && (ft_is_logical_operators(shell,
						shell->i) || ft_is_redirections(shell, shell->i)))
			|| ((ft_is_logical_operators(shell, shell->i))
				&& (ft_is_logical_operators(shell, shell->i + 1)))
			|| ((ft_is_redirections(shell, shell->i))
				&& (ft_is_redirections(shell, shell->i + 1)))
			|| (!ft_strcmp(shell->temp[shell->i], "&")))
		{
			ft_free_args(shell);
			return ;
		}
		else if (shell->temp[shell->i] && shell->temp[shell->i + 1])
			ft_remainder_of_this_function(shell);
		shell->i++;
	}
}

void	ft_check_the_brackets(t_parsing *shell)
{
	if (shell->free == -1)
		return ;
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		shell->j = 0;
		while (shell->temp[shell->i][shell->j] && shell->temp[shell->i][0] != 34
			&& shell->temp[shell->i][0] != 39
			&& shell->temp[shell->i][ft_strlen(shell->temp[shell->i]) - 1] != 34
			&& shell->temp[shell->i][ft_strlen(shell->temp[shell->i])
			- 1] != 39)
		{
			if (shell->temp[shell->i][shell->j] == '(')
				shell->brackets++;
			if (shell->temp[shell->i][shell->j] == ')')
				shell->brackets--;
			shell->j++;
		}
		if (shell->brackets < 0)
		{
			ft_free_args(shell);
			return ;
		}
		shell->i++;
	}
}

t_list	*ft_creat_new_node(t_parsing *shell, int start, int end)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = malloc((end - start + 2) * sizeof(char *));
	if (!new->value)
		return (NULL);
	shell->len = 0;
	while (start <= end)
	{
		new->value[shell->len] = ft_strdup(shell->temp[start]);
		shell->len++;
		start++;
	}
	new->value[shell->len] = NULL;
	new->next = NULL;
	return (new);
}

int	ft_is_symbol(t_parsing *shell)
{
	if (!shell->temp[shell->i])
		return (0);
	if (!ft_strcmp(shell->temp[shell->i], "|")
		|| !ft_strcmp(shell->temp[shell->i], ")")
		|| !ft_strcmp(shell->temp[shell->i], "(")
		|| !ft_strcmp(shell->temp[shell->i], "<")
		|| !ft_strcmp(shell->temp[shell->i], ">")
		|| !ft_strcmp(shell->temp[shell->i], "<<")
		|| !ft_strcmp(shell->temp[shell->i], ">>")
		|| !ft_strcmp(shell->temp[shell->i], "||")
		|| !ft_strcmp(shell->temp[shell->i], "&&"))
		return (1);
	return (0);
}

void	ft_tokens_list(t_parsing *shell)
{
	if (!shell || !shell->temp || !shell->temp[0])
		return ;
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		shell->j = shell->i;
		if (!ft_is_symbol(shell) && !ft_is_redirections(shell, shell->i))
		{
			while (shell->temp[shell->i] && !ft_is_symbol(shell)
				&& !ft_is_redirections(shell, shell->i))
				shell->i++;
		}
		else if (ft_is_symbol(shell))
			shell->i++;
		shell->lst_help1 = ft_creat_new_node(shell, shell->j, --shell->i);
		if (!shell->lst_help1)
			return ;
		if (!shell->tokens)
			shell->tokens = shell->lst_help1;
		else
			shell->lst_help2->next = shell->lst_help1;
		shell->lst_help2 = shell->lst_help1;
		shell->i++;
	}
}

void	ft_check_syntax_errors(t_parsing *shell)
{
	ft_check_the_brackets(shell);
	if (shell->brackets != 0)
		ft_free_args(shell);
	ft_check_operator_position(shell);
	ft_tokens_list(shell);
}

int	ft_check_input_is_valid(t_parsing *shell)
{
	if (!shell || !shell->input)
		return (0);
	shell->i = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] != ' ' && shell->input[shell->i] != '\t'
			&& shell->input[shell->i] != '\n')
			break ;
		shell->i++;
	}
	shell->len = ft_strlen(shell->input);
	if (shell->len != shell->i)
	{
		shell->i = 0;
		shell->len = 0;
		return (1);
	}
	return (0);
}

int	ft_check_single_operators(t_parsing *shell)
{
	if ((shell->input[shell->i]) && (shell->input[shell->i] == '|'
			|| shell->input[shell->i] == '<' || shell->input[shell->i] == '>'
			|| shell->input[shell->i] == '(' || shell->input[shell->i] == ')'
			|| shell->input[shell->i] == ':' || shell->input[shell->i] == '~'
			|| shell->input[shell->i] == '#' || shell->input[shell->i] == '&'))
		return (1);
	return (0);
}

int	ft_check_double_operators(t_parsing *shell)
{
	if ((shell->input[shell->i] && shell->input[shell->i + 1])
		&& ((shell->input[shell->i] == '|' && shell->input[shell->i + 1] == '|')
			|| (shell->input[shell->i] == '&' && shell->input[shell->i
				+ 1] == '&') || (shell->input[shell->i] == '>'
				&& shell->input[shell->i + 1] == '>')
			|| (shell->input[shell->i] == '<' && shell->input[shell->i
				+ 1] == '<') || (shell->input[shell->i] == '$'
				&& shell->input[shell->i + 1] == '?')))
		return (1);
	return (0);
}

void	ft_skip_string(t_parsing *shell)
{
	shell->len += 2;
	shell->chr = shell->input[shell->i];
	while (shell->input[shell->i])
	{
		shell->i++;
		shell->len++;
		if ((shell->input[shell->i]) && (shell->input[shell->i] == shell->chr))
			return ;
	}
	ft_free_args(shell);
}

void	ft_count_len_args(t_parsing *shell)
{
	shell->i = 0;
	shell->len = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
			ft_skip_string(shell);
		else if (ft_check_double_operators(shell))
		{
			shell->i++;
			shell->len += 3;
		}
		else if (ft_check_single_operators(shell))
			shell->len += 2;
		shell->i++;
		shell->len++;
	}
}

void	ft_str_copy(t_parsing *shell)
{
	shell->cmds[shell->len++] = '\n';
	shell->chr = shell->input[shell->i];
	while (shell->input[shell->i])
	{
		shell->cmds[shell->len++] = shell->input[shell->i++];
		if (shell->input[shell->i] == shell->chr)
		{
			shell->cmds[shell->len++] = shell->input[shell->i];
			shell->cmds[shell->len++] = '\n';
			return ;
		}
	}
	ft_free_args(shell);
}

void	ft_this_condition_function(t_parsing *shell)
{
	if (shell->input[shell->i] == '~' || shell->input[shell->i] == '$')
	{
		shell->cmds[shell->len++] = '\n';
		shell->cmds[shell->len++] = '\n';
		shell->cmds[shell->len++] = shell->input[shell->i];
	}
	else if (shell->input[shell->i] == ':')
	{
		shell->cmds[shell->len++] = shell->input[shell->i];
		shell->cmds[shell->len++] = '\n';
		shell->cmds[shell->len++] = '\n';
	}
	else
	{
		shell->cmds[shell->len++] = '\n';
		shell->cmds[shell->len++] = shell->input[shell->i];
		shell->cmds[shell->len++] = '\n';
	}
}

void	ft_args_copy(t_parsing *shell)
{
	if (!shell->input || !shell->input[0] || shell->bol == -1)
		ft_free_args(shell);
	shell->i = 0;
	shell->len = 0;
	while (shell->input && shell->input[shell->i])
	{
		if (shell->input[shell->i] == 34 || shell->input[shell->i] == 39)
			ft_str_copy(shell);
		else if (ft_check_double_operators(shell))
		{
			shell->cmds[shell->len++] = '\n';
			shell->cmds[shell->len++] = shell->input[shell->i];
			shell->cmds[shell->len++] = shell->input[++shell->i];
			shell->cmds[shell->len++] = '\n';
		}
		else if (ft_check_single_operators(shell))
			ft_this_condition_function(shell);
		else if (shell->input[shell->i] == ' '
				|| shell->input[shell->i] == '\t')
			shell->cmds[shell->len++] = '\n';
		else
			shell->cmds[shell->len++] = shell->input[shell->i];
		if (shell->input[shell->i])
			shell->i++;
	}
}

void	ft_delete_commits(t_parsing *shell)
{
	shell->i = 0;
	while (shell->temp[shell->i])
	{
		if (!ft_strcmp(shell->temp[shell->i], "#"))
		{
			while (shell->temp[shell->i])
			{
				free(shell->temp[shell->i]);
				shell->temp[shell->i] = NULL;
				shell->i++;
			}
			return ;
		}
		shell->i++;
	}
}

void	ft_split_args(t_parsing *shell)
{
	ft_count_len_args(shell);
	if (shell->free == -1)
		return ;
	shell->cmds = malloc(shell->len + 1);
	if (!shell->cmds)
		return ;
	ft_args_copy(shell);
	shell->cmds[shell->len] = '\0';
	shell->temp = ft_split(shell->cmds, '\n');
	if (!shell->temp)
		ft_free_args(shell);
	if (shell->free == -1)
		return ;
	ft_delete_commits(shell);
}

int	ft_count_nodes_list(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

int	ft_count_brackets(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->value && (!ft_strcmp(list->value[0], "(")
				|| !ft_strcmp(list->value[0], ")")))
			count++;
		list = list->next;
	}
	return (count);
}

//----------------------------------------------------------------

t_ast	*ft_create_ast_node(char **value)
{
	t_ast	*new;
	int		i;

	if (!value || !value[0])
		return (NULL);
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	i = 0;
	while (value[i])
		i++;
	new->value = malloc(sizeof(char *) * (i + 1));
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (value[i])
	{
		new->value[i] = ft_strdup(value[i]);
		i++;
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_list	*ft_get_lst_node(t_list *tokens, int n)
{
	t_list	*temp;

	temp = tokens;
	while (n-- > 0 && temp)
		temp = temp->next;
	return (temp);
}

t_ast	*ft_build_command_tree(t_parsing *shell, int start, int end)
{
	t_ast	*tree;
	int		i;

	if (start > end || !shell || shell->free == -1)
		return (NULL);
	shell->start_node = ft_get_lst_node(shell->tokens, start);
	shell->end_node = ft_get_lst_node(shell->tokens, end);
	if (!shell->start_node || !shell->start_node->value || !shell->end_node
		|| !shell->end_node->value)
		return (NULL);
	if (shell->start_node->value[0][0] == '('
		&& shell->end_node->value[0][0] == ')')
	{
		shell->brackets = 1;
		i = start + 1;
		shell->lst_help1 = shell->start_node->next;
		while (i < end)
		{
			if (!shell->lst_help1)
				break ;
			else if (shell->lst_help1->value[0][0] == '(')
				shell->brackets++;
			else if (shell->lst_help1->value[0][0] == ')')
				shell->brackets--;
			if (shell->brackets == 0)
				break ;
			shell->lst_help1 = shell->lst_help1->next;
			i++;
		}
		if (shell->brackets == 1)
			return (ft_build_command_tree(shell, start + 1, end - 1));
	}
	shell->priority = 0;
	while (shell->priority < 3)
	{
		shell->parent = 0;
		i = end;
		shell->lst_help2 = ft_get_lst_node(shell->tokens, end);
		while (i >= start)
		{
			if (!shell->lst_help2)
				break ;
			else if (shell->lst_help2->value[0][0] == '(')
				shell->parent++;
			else if (shell->lst_help2->value[0][0] == ')')
				shell->parent--;
			if (shell->parent == 0)
			{
				if (shell->priority == 0
					&& (!ft_strcmp(shell->lst_help2->value[0], "||")
						|| !ft_strcmp(shell->lst_help2->value[0], "&&")))
				{
					tree = ft_create_ast_node(shell->lst_help2->value);
					if (!tree)
						return (NULL);
					tree->left = ft_build_command_tree(shell, start, i - 1);
					tree->right = ft_build_command_tree(shell, i + 1, end);
					return (tree);
				}
				else if (shell->priority == 1
						&& (!ft_strcmp(shell->lst_help2->value[0], "|")))
				{
					tree = ft_create_ast_node(shell->lst_help2->value);
					if (!tree)
						return (NULL);
					tree->left = ft_build_command_tree(shell, start, i - 1);
					tree->right = ft_build_command_tree(shell, i + 1, end);
					return (tree);
				}
				else if (shell->priority == 2
						&& (!ft_strcmp(shell->lst_help2->value[0], "<")
							|| !ft_strcmp(shell->lst_help2->value[0], ">")
							|| !ft_strcmp(shell->lst_help2->value[0], "<<")
							|| !ft_strcmp(shell->lst_help2->value[0], ">>")))
				{
					tree = ft_create_ast_node(shell->lst_help2->value);
					if (!tree)
						return (NULL);
					tree->left = ft_build_command_tree(shell, start, i - 1);
					tree->right = ft_build_command_tree(shell, i + 1, end);
					return (tree);
				}
			}
			shell->lst_help2 = ft_get_lst_node(shell->tokens, i - 1);
			i--;
		}
		shell->priority++;
	}
	if (start <= end)
		return (ft_create_ast_node(shell->start_node->value));
	return (NULL);
}

t_ast	*ft_create_ast_tree(t_parsing *shell)
{
	if (!shell || !shell->tokens)
		return (NULL);
	shell->i = 0;
	shell->lst_help1 = shell->tokens;
	while (shell->lst_help1)
	{
		shell->i++;
		shell->lst_help1 = shell->lst_help1->next;
	}
	return (ft_build_command_tree(shell, 0, shell->i - 1));
}

void	print_ast(t_ast *node, int level, char *branch)
{
	int	i;
	int	j;

	if (!node || !node->value || !node->value[0])
		return ;
	i = 0;
	while (i < level)
	{
		printf("   ");
		i++;
	}
	printf("[%s]   ", branch);
	if (node->value)
	{
		j = 0;
		while (node->value[j])
		{
			printf("%s ", node->value[j]);
			j++;
		}
	}
	printf("\n");
	print_ast(node->left, level + 1, "left");
	print_ast(node->right, level + 1, "right");
}

//----------------------------------------------------------------

void	ft_parsing(t_parsing *shell)
{
	ft_init_parsing(shell);
	if (ft_check_input_is_valid(shell))
	{
		ft_split_args(shell);
		ft_check_syntax_errors(shell);
		shell->three = ft_create_ast_tree(shell);
		if (!shell->three)
			return ;
		print_ast(shell->three, 0, "root");
	}
}

int	main(int ac, char **av, char **env)
{
	t_parsing	shell;

	if (ac != 1)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		exit(-1);
	}
	while (1)
	{
		shell.input = readline("➜ Minishell ");
		ft_parsing(&shell);
		if (shell.free == -1 && (!shell.tokens || !shell.three))
			write(2, "minishell: syntax error\n", 24);
		if (shell.input)
		{
			add_history(shell.input);
			ft_free_parsing(&shell);
		}
	}
	rl_clear_history();
	(void)av;
	return (0);
}
