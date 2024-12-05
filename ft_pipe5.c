#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: %s <string>\n", av[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];
    pid_t pid;
    ssize_t len;
    int count;
    char buffer[1337];

    if (pipe(fd) < 0)
    {
        printf("Error creating pipe: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
    {
        printf("Error creating process: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        close(fd[0]);
        if (write(fd[1], av[1], strlen(av[1])) < 0)
        {
            printf("Error writing to pipe: %s\n", strerror(errno));
        }
        close(fd[1]);
        wait(NULL);
    }
    else 
    {
        close(fd[1]);
        len = read(fd[0], buffer, sizeof(buffer) - 1);
        if (len < 0)
        {
            printf("Error reading from pipe: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(fd[0]);

        buffer[len] = '\0';
        count = 0;
        for (ssize_t i = 0; i < len; i++)
        {
            if (buffer[i] == ' ')
                count++;
        }
        printf("Result: %d\n", count);
    }

    return 0;
}

