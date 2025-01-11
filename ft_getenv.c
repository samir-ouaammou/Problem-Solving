#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char    *path = getenv("PATH");
    if (!path)
        printf("(null)\n");
    else
        printf("path => %s\n", path);
    return (0);
}