#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

static int  ft_strchr(const char *str, char c)
{
    size_t  i;  // index

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

static size_t   ft_strlen(const char *str)
{
    size_t  l;  //  length

    if (!str)
        return (0);

    l = 0;
    while(str[l])
        l++;

    return (l);
}

static char *ft_strdup(const char *temp)
{
    char    *res;   //  result
    int     i;  // index

    if (!temp)
        return (ft_strdup(""));
    res = (char *)malloc(ft_strlen(temp) + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (temp[i])
    {
        res[i] = temp[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

static char *ft_strjoin(const char *s1, const char *s2)
{
    char    *res;   // result
    size_t  i;      // index1
    size_t  j;      // index2

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        s1 = ft_strdup("");
    if (!s2)
        s2 = ft_strdup("");
    res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!res)
        return (NULL);
    i = -1;
    while (s1[++i])
        res[i] = s1[i];
    j = -1;
    while (s2[++j])
        res[i + j] = s2[j];
    res[i + j] = '\0';
    return (res);
}

static char *ft_read_buffer_size(int fd, char **save)
{
    char    *buffer;
    char    *temp;
    ssize_t  len;

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return ((free(*save)), (*save = NULL), (buffer = NULL), (NULL));
    while (!ft_strchr(*save, '\n'))
    {
        len = read(fd, buffer, BUFFER_SIZE);
        if (len <= 0)
            break;
        buffer[len] = '\0';
        temp = ft_strjoin(*save, buffer);
        if (!temp)
            return ((free(*save)), (*save = NULL), (free(buffer)), (buffer = NULL), (NULL));
        *save = temp;
    }
    return ((free(buffer)), (buffer = NULL), *save);
}

static char *ft_read_line(char **save)
{
    char    *line;
    size_t  i;  // index1
    size_t  j;  // index2

    if (!*save || !*save[0])
        return (NULL);
    i = 0;
    while (*save[i] && *save[i] != '\n')
        i++;
    if (*save[i] == '\n')
        i++;
    line = (char *)malloc((i + 1) * sizeof(char));
    if (!line)
        return ((free(*save)), (*save = NULL), NULL);
    j = 0;
    while (j < i)
    {
        line[j] = *save[j];
        j++;
    }
    line[j] = '\0';
    *save = &*save[i];
    return (line);
}

static char *ft_git_next_line(ssize_t fd)
{
    static char *save;  // save next line
    char        *line;
    char        *temp;

    if ((fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, 0, 0) < 0))
        return (NULL);
    temp = ft_read_buffer_size(fd, &save);
    if (!temp)
        return ((temp = NULL), (NULL));
    line = ft_read_line(&temp);
    if (!line)
        return (free(temp), temp = NULL, NULL);
    save = ft_strdup(temp);
    return (free(temp), temp = NULL, line);
}

int main(void)
{
    ssize_t fd;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        perror("error opening file");
    else
    {
        printf("%s\n", ft_git_next_line(fd));
        printf("%s\n", ft_git_next_line(fd));
        printf("%s\n", ft_git_next_line(fd));
        printf("%s\n", ft_git_next_line(fd));
        printf("%s\n", ft_git_next_line(fd));
    }
    return (0);
}