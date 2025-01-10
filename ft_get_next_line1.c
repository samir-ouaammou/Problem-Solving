#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// وظيفة لحساب طول النص
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// وظيفة للبحث عن '\n' في النص
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// وظيفة لجمع النصوص
char	*ft_strjoin(char *s1, char *s2)
{
	int		len1 = ft_strlen(s1), len2;
	char	*result;
	int		i;
	int		j;

	len1 = ft_strlen(s1), len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		result[i++] = s2[j++];
	}
	result[i] = '\0';
	free(s1);
	return (result);
}

// وظيفة لاستخراج السطر من النص المحفوظ
char	*extract_line(char **saved)
{
	char	*line;
	char	*new_saved;
	int		i;

	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = (*saved)[j];
	line[i] = '\0';
	new_saved = ft_strjoin(NULL, *saved + i);
	free(*saved);
	*saved = new_saved;
	return (line);
}

// الوظيفة الرئيسية
char	*get_next_line(int fd)
{
	static char	*saved;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(saved), saved = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		saved = ft_strjoin(saved, buffer);
		if (!saved)
			return (NULL);
	}
	if (!saved || !*saved)
		return (free(saved), saved = NULL, NULL);
	return (extract_line(&saved));
}
