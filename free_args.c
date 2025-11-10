#include "shell.h"

/* free_args - frees an array of strings */
void free_args(char **args)
{
    int i;

    if (args == NULL)
        return;

    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}
