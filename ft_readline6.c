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
			i = 0;
			history = history_list();
			while (history[i])
			{
				printf("%s\n", history[i]->line);
				i++;
			}
		}
		if (!strcmp(input, "history -c"))
			rl_clear_history();
		free(input);
		input = NULL;
	}
	return (0);
}
