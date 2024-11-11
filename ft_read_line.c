#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

char    *ft_read_line(void)
{
    char        *buffer;
    char        *temp;
    size_t      index;
    ssize_t     help;
    char        c;

    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!buffer)
        return (NULL);
    index = 0;
    while((help = read(0, &c, BUFFER_SIZE) > 0) && (c != '\n'))
    {
        temp = (char *)realloc(buffer, index + 2);
        if (!temp)
            return (NULL);
        buffer = temp;
        buffer[index] = c;
        index++;
    }
    if (help == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[index] = '\0';
    return (buffer);
}

int main(void)
{
    char    *result;

    result = ft_read_line();
    if (!result)
        printf("(null)\n");
    else
        printf("%s\n", result);

    return (0);
}