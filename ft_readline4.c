#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char		*input;
	int			i;
	HIST_ENTRY	**history;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;
		add_history(input);
		if (!strcmp(input, "history"))
		{
			history = history_list();
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
