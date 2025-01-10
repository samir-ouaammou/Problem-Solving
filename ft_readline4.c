#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	int	i;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;
		add_history(input);
		if (!strcmp(input, "history"))
		{
			HIST_ENTRY **history = history_list();
			i = 1;
			while (history[i])
			{
				printf("%s\n", history[i - 1]->line);
				i++;
			}
		}
		free(input);
	}
	return (0);
}
