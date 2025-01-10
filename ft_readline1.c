#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("What's your name: ");
		if (strlen(input) >= 2)
		{
			write (1, "Your name is: ", 14);
			write (1, input, strlen(input));
			write (1, "\n", 1);
			free(input);
			input = NULL;
			return (0);
		}
		free(input);
		input = NULL;
	}
	return (0);
}
