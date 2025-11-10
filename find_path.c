#include "shell.h"

/* find_path - finds the full path of a command */
char *find_path(char *cmd, char **env)
{
    char *path, *dir, *full_path;
    char *path_copy;
    size_t len;
    struct stat st;

    if (cmd == NULL || env == NULL)
        return NULL;

    if (strchr(cmd, '/') != NULL) /* command already contains '/' */
        return strdup(cmd);

    path = _getenv("PATH", env);
    if (path == NULL)
        return NULL;

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + 1 + strlen(cmd) + 1;
        full_path = malloc(len);
        if (full_path == NULL)
        {
            perror("malloc");
            free(path_copy);
            exit(EXIT_FAILURE);
        }
        sprintf(full_path, "%s/%s", dir, cmd);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}
