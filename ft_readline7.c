#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;

	input = readline("Enter command: ");
	if (input)
	{
		printf("Processing input...\n");
		rl_on_new_line();
		rl_replace_line("Updated command>", 0);
		rl_redisplay();
		free(input);
	}
	return (0);
}
