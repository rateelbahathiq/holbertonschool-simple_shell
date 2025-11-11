#include "main.h"
#include <string.h>

char *_getenv(const char *name, char **env)
{
    int i = 0;
    size_t len = strlen(name);

    while (env[i])
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}
