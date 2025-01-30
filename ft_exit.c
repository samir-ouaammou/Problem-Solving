#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;
		add_history(input);
		printf("=> %s\n", input);
		free(input);
		input = NULL;
	}
	free(input);
	input = NULL;
	return (0);
}
