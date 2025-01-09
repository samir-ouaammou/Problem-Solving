#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;
	while (1)
	{
		line = readline("$> ");
		if (!line[0])
			break;
		printf("=> %s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (0);
}
