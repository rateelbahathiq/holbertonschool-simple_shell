#include "shell.h"

/* run_command - run a command */
void run_command(char **args, char **env)
{
    pid_t pid;
    int status;
    char *command_path;

    if (args == NULL || args[0] == NULL)
        return;

    if (_strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        exit(EXIT_SUCCESS);
    }

    command_path = find_path(args[0], env);
    if (command_path == NULL)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", args[0], args[0]);
        return;
    }

    pid = fork();
    if (pid == 0) /* child */
    {
        if (execve(command_path, args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) /* parent */
        wait(&status);
    else
        perror("fork");

    free(command_path);
}

