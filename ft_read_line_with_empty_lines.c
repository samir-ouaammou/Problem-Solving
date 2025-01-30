#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

char	*ft_read_line_with_empty_line(ssize_t fd)
{
	char	*buffer;
	char	*help;
	size_t	index;
	ssize_t	temp;
	char	c;

	buffer = (char *)malloc(sizeof(char));
	if (!buffer)
		return (NULL);
	index = 0;
	while ((temp = read(fd, &c, BUFFER_SIZE) > 0) && (c != '\n'))
	{
		help = (char *)realloc(buffer, index + 2);
		if (!help)
		{
			free(buffer);
			return (NULL);
		}
		buffer = help;
		buffer[index] = c;
		index++;
	}
	if (temp == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[index] = '\0';
	return (buffer);
}

ssize_t	ft_open_file(char *file)
{
	ssize_t	fd;

	fd = open(file, O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
		perror("error opening file");
	return (fd);
}

int	main(void)
{
	ssize_t fd;
	char *result;

	fd = ft_open_file("file.txt");
	if (fd >= 0)
	{
		result = ft_read_line_with_empty_line(fd);
		if (!result)
			printf("error\n");
		else
			printf("%s\n", result);
	}

	return (0);
}