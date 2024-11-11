#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1

char    *ft_read_line_from_file(ssize_t fd)
{
    char    *buffer;
    char    *help;
    ssize_t temp;
    size_t  index;
    char    c;

    if (fd == -1)
        return (NULL);
    buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
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

int main(void)
{
    ssize_t     fd;
    char    *result;

    fd = open("file.txt", O_CREAT | O_RDONLY, 0644);
    if (fd == -1)
        perror("error");
    else
    {
        result = ft_read_line_from_file(fd);
        if (!result)
            printf("(null)\n");
        else
            printf("%s\n", result);
    }
    return (0);
}