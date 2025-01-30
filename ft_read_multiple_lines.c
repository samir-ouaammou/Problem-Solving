#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

void	*ft_free(char **result, size_t word_count)
{
	if (word_count > 0)
	{
		word_count--;
		free(result[word_count]);
	}
	free(result);
	return (NULL);
}

void	ft_mvwrd(char **result, char *temp, size_t index)
{
	int	i;

	result[index] = (char *)malloc((ft_strlen(temp) + 1) * sizeof(char));
	if (!result[index])
		return ;
	i = 0;
	while (temp[i])
	{
		result[index][i] = temp[i];
		i++;
	}
	result[index][i] = '\0';
}

char	**ft_read_multiplr_lines(ssize_t fd, int num_lines)
{
	char	**buffer;
	char	help[1024];
	size_t	index1;
	size_t	index2;
	ssize_t	tmp;
	char	c;

	buffer = (char **)malloc(num_lines * sizeof(char *));
	if (!buffer)
		return (NULL);
	index1 = 0;
	while (index1 < num_lines)
	{
		index2 = 0;
		while ((tmp = read(fd, &c, BUFFER_SIZE) >= 0) && c != '\n')
		{
			help[index2] = c;
			index2++;
		}
		if (tmp == -1)
			return (ft_free(buffer, index1));
		help[index2] = '\0';
		ft_mvwrd(buffer, help, index1);
		if (!buffer[index1])
			return (ft_free(buffer, index1));
		index1++;
	}
	return (buffer);
}

ssize_t	ft_open_file(void)
{
	ssize_t	fd;

	fd = open("file.txt", O_CREAT | O_RDONLY, 0644);
	return (fd);
}

int	main(void)
{
	ssize_t fd;
	char **result;

	fd = ft_open_file();
	if (fd == -1)
		perror("error opening file");
	else
	{
		result = ft_read_multiplr_lines(fd, 3);
		if (!result)
			printf("NULL\n");
		else
		{
			fd = 0;
			while (result[fd])
			{
				printf("len fd =>   { %s }\n", result[fd]);
				free(result[fd]);
				fd++;
			}
		}
	}
	return (0);
}