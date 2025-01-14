#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char    path[1000];

    if (getcwd(path, sizeof(path)))
        printf("path => %s\n", path);

    if (!chdir("/Desktop"))
        if (getcwd(path, sizeof(path)))
            printf("path => %s\n", path);
    return (0);
}
