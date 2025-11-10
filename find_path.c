#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

char *find_path(char *command, char **env)
{
    char *path_env = _getenv("PATH", env);
    char *path_copy, *dir, *full_path;
    size_t len;

    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = strlen(dir) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(full_path, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}
