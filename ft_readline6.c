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
			break;
		add_history(input);
		if (!strcmp(input, "history"))
		{
			i = 0;
			HIST_ENTRY **history = history_list();
			while (history[i])
			{
				printf("%s\n", hestory[i]->line);
				i++;
			}
		}
		free(input);
		input = NULL;
	}
	return (0);
}
