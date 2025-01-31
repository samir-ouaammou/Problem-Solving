#include <stdlib.h>

static int	ft_word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_strdup_range(const char *start, const char *end)
{
	int		len;
	char	*word;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	for (int i = 0; i < len; i++)
		word[i] = start[i];
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int			words;
	char		**result;
	int			i;
	const char	*start;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i++] = ft_strdup_range(start, s);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
