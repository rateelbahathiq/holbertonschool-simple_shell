#include <string.h> /* for strlen, strncmp */
#include <stdlib.h>

/* Get the value of an environment variable */
char *_getenv(const char *name, char **env)
{
    int i, len;

    if (!name || !env)
        return NULL;

    len = strlen(name);
    for (i = 0; env[i]; i++)
    {
        if (strncmp(name, env[i], len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
    }
    return NULL;
}
