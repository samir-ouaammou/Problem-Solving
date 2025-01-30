#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (!input || !input[0] || !strcmp(input, "exit"))
			break ;
		printf("=> %s\n%zu\n", input, strlen(input));
		free(input);
		input = NULL;
	}
	free(input);
	input = NULL;
	return (0);
}
