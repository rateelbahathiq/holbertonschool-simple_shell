#include "shell.h"

/* _getenv - get the value of an environment variable */
char *_getenv(const char *name, char **env)
{
    int i, len;

    if (name == NULL || env == NULL)
        return NULL;

    len = strlen(name);
    for (i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
    }
    return NULL;
}
