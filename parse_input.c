#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char **parse_input(char *line)
{
    char *token;
    char **args;
    int i = 0;
    int bufsize = 64;

    args = malloc(sizeof(char *) * bufsize);
    if (!args)
        return (NULL);

    token = strtok(line, " \t\r\n");
    while (token)
    {
        args[i++] = strdup(token);
        if (i >= bufsize)
        {
            bufsize += 64;
            args = realloc(args, sizeof(char *) * bufsize);
            if (!args)
                return (NULL);
        }
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
    return (args);
}
