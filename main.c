#include "main.h"

extern char **environ;

int main(void)
{
    char *line = NULL;
    char **args = NULL;

    while (1)
    {
        display_prompt();              /* show "$ " only if TTY */

        line = read_line();            /* NULL on EOF (Ctrl+D) */
        if (!line) {
            if (isatty(STDIN_FILENO)) write(STDOUT_FILENO, "\n", 1);
            break;
        }

        args = parse_input(line);      /* tokens reference 'line' */
        if (args && args[0])
            run_command(args, environ);/* 0.2: resolve first, don't fork if missing */

        free_args(args);               /* frees only the array */
        free(line);                    /* free the owning buffer */
    }
    return 0;
}
