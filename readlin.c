#include <readline/readline.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void j(int s)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("hello", 0);
    rl_redisplay();
}
int main(int argc, char const *argv[])
{
    signal(SIGINT, j);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        char *u = readline("xlo7 $ ");
        system(u);
    }

    return 0;
}
