#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (free(s1), ft_strdup(s1));
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
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
	int		len;
	int		i;

	buffer = malloc((BUFFER_SIZE * sizeof(char) + 1));
	if (!buffer)
		return (free(save), save = NULL, NULL);
	while (1)
	{
		if (save)
		{
			i = 0;
			while (save[i])
			{
				if (save[i] == '\n')
					return (free(buffer), save);
				i++;
			}
		}
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
			return (free(save), save = NULL, free(buffer), NULL);
		if (len == 0)
			break ;
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
	int		i;
	int		j;

	if (!*save)
		return (NULL);
	if (!(*save)[0])
		return (free(save), save = NULL, NULL);
	i = 0;
	while ((*save)[i] && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (free(*save), *save = NULL, NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*save)[j];
		j++;
	}
	line[j] = '\0';
	next_line = ft_strdup(&((*save)[i]));
	free(*save);
	if (!next_line)
		*save = NULL;
	else
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
	if (!line)
		return (NULL);
	if (save && !save[0])
		return (free(save), save = NULL, line);
	return (line);
}
