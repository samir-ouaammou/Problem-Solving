#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (!strcmp(input, "exit"))
			break ;
		free(input);
	}
	free(input);
	return (0);
}
