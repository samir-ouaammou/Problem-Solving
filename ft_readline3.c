#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int			i;
	char		*input;
	HIST_ENTRY	**history;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;
		add_history(input);
		i = 0;
		history = history_list();
		while (history[i + 1])
		{
			if (!strcmp(history[i]->line, input))
			{
				write(1, "The entry alridy ecists\n", 24);
				free(input);
				return (0);
			}
			i++;
		}
		free(input);
	}
	free(input);
	return (0);
}
