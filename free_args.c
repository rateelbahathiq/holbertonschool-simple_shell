#include <stdlib.h>
#include "shell.h"

void free_args(char **args)
{
    if (!args)
        return;

    free(args);
}
