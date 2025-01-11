#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef	BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

int	ft_strlen(const char *str)
{
	int	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*res;
	int	i = 0;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	int	i = 0;
	int	j = 0;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);

	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';

	free(s1);
	return (res);
}

char	*ft_read_buffer_size(int fd, char *save)
{
	char	*buffer;
	int	len;
	int	i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(save), NULL);

	while (1)
	{
		i = 0;
		while (save && save[i])
		{
			if (save[i] == '\n')
				return (free(buffer), save);
			i++;
		}
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
			return (free(save), free(buffer), NULL);
		if (len == 0)
			break;
		buffer[len] = '\0';
		save = ft_strjoin(save, buffer);
		if (!save)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (save);
}

char	*ft_read_line(char **save)
{
	char	*line;
	char	*next_line;
	int	i = 0;
	int	j = 0;

	if (!(*save))
		return (NULL);
	if (!(*save)[0])
		return (free(*save), *save = NULL, NULL);

	while ((*save)[i] && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		i++;

	line = malloc(i + 1);
	if (!line)
		return (free(*save), *save = NULL, NULL);

	while (j < i)
	{
		line[j] = (*save)[j];
		j++;
	}
	line[j] = '\0';

	next_line = ft_strdup(&(*save)[i]);
	free(*save);
	*save = next_line;

	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	save = ft_read_buffer_size(fd, save);
	if (!save)
		return (NULL);

	line = ft_read_line(&save);
	if (save && !save[0])
	{
		free(save);
		save = NULL;
	}
	return (line);
}

