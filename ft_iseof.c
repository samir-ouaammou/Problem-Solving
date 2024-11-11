#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int ft_is_eof(ssize_t   fd)
{
    char    temp;
    ssize_t size;

    size = read(fd, &temp, 1);
    if (size == 0)
        return(1);
    else
        return (0);
}

int main(void)
{
    ssize_t fd;
    short result;

    fd = open("file.txt", O_CREAT | O_RDONLY, 0644);
    if (fd == -1)
        perror ("error opening file");
    else
    {
        result = ft_is_eof(fd);
        printf("%d\n", result);
    }

    return (0);
}