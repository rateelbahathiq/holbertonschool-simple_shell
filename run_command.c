#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int run_command(char **args, char **av, char **env)
{
    pid_t pid;
    int status;
    char *command_path;

    if (!args || !args[0])
        return 1;

    command_path = find_path(args[0], env);
    if (!command_path)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
        return 127;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(command_path);
        return 1;
    }

    if (pid == 0) /* Child */
    {
        if (execve(command_path, args, env) == -1)
        {
            perror("execve");
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent */
    {
        wait(&status);
    }

    free(command_path);
    return status;
}
