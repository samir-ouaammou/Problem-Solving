#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;

		if (!strcmp(input, "history"))
		{
			HIST_ENTRY **history = history_list();
			if (history)
			{
				int	i = 0;
				while (history[i] != NULL)
				{
					printf("%s\n", history[i]->line);
					i++;
				}
			}
		}

		add_history(input);
		printf("=> %s\nlen => %lu\n", input, strlen(input));

		free(input);
		input = NULL;
	}
	
	free(input);
	input = NULL;
	return (0);
}
