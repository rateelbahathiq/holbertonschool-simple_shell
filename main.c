#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;

    (void)ac;
    (void)av;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        args = parse_input(line);
        if (!args)
            continue;

        if (_strcmp(args[0], "exit") == 0)
        {
            free_args(args);
            break;
        }

        run_command(args, env);
        free_args(args);
    }

    free(line);
    return (0);
}
