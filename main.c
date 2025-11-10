#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    size_t n = 0;
    char **args;

    (void)ac;

    while (1)
    {
        printf("$ ");
        if (getline(&line, &n, stdin) == -1)
        {
            free(line);
            break;
        }

        args = parse_input(line);
        if (args == NULL)
            continue;

        run_command(args, env, av);
        free_args(args);
    }

    return 0;
}
