#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int run_command(char **args, char **env)
{
    pid_t pid;
    int status;

    if (!args || !args[0])
        return (1);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }

    if (pid == 0)
    {
        if (execve(args[0], args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }

    return (0);
}
