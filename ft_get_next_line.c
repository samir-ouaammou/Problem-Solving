#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(const char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

    if (!s1 || !s2)
        return (NULL);
	i = ft_strlen (s1);
	j = 0;
	while (s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

char	*ft_strdup(const char *str)
{
	char	*res;
	int		i;

	res = (char *)malloc(ft_strlen(str) + 1);
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

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	free(s1);
    s1 = NULL;
	return (res);
}

char	*read_buffer_size(int fd, char *save)
{
	char	*buffer;
	char	*temp;
	int		len;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(save), save = NULL, NULL);
	while (!ft_strchr(save, '\n'))
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buffer[len] = '\0';
		temp = ft_strjoin(save, buffer);
		if (!temp)
			return (free(save), save = NULL, free(buffer), buffer = NULL, NULL);
		save = temp;
	}
	return (free(buffer), buffer = NULL, save);
}

char	*read_line(char **save)
{
	char	*line;
	int		i;
	int		j;

	if (!(*save) || !(*save)[0])
		return (free(save), save = NULL, NULL);
	i = 0;
	while ((*save)[i] && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (free(save), save = NULL, NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*save)[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*read_next_line(char **temp)
{
	char	*save;
	int		i;
	int		j;

	if (!(*temp) || !(*temp)[0])
		return (free(*temp), (*temp) = NULL, NULL);
	i = 0;
	while ((*temp)[i] && (*temp)[i] != '\n')
		i++;
	if ((*temp)[i] == '\n')
		i++;
	save = (char *)malloc((ft_strlen(*temp) - i) + 1);
	if (!save)
		return (free(*temp), *temp = NULL, NULL);
	j = 0;
	while ((*temp)[i + j])
	{
		save[j] = (*temp)[i + j];
		j++;
	}
	save[j] = '\0';
	return (free(*temp), *temp = NULL, save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (0);
	save = read_buffer_size(fd, save);
	if (!save)
		return (NULL);
	line = read_line(&save);
	if (!line)
		return (NULL);
	save = read_next_line(&save);
	if (save && !save[0])
		return (free(save), save = NULL, line);
	return (line);
}

int	main(void)
{
	int fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		printf("error opening file\n");
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	return (0);
}