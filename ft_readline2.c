#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

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
