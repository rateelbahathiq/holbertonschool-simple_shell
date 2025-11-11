#include "main.h"

extern char **environ;

int main(int ac, char **av)
{
    char *line = NULL;
    char **args = NULL;
    int lineno = 0;
    int last_status = 0;
    const char *prog = (av && av[0]) ? av[0] : "./hsh";

    (void)ac; /* unused */

    while (1)
    {
        display_prompt();

        line = read_line(); /* NULL on EOF */
        if (!line) {
            if (isatty(STDIN_FILENO)) write(STDOUT_FILENO, "\n", 1);
            break;
        }

        lineno++; /* increment command line count */

        args = parse_input(line);
        if (args && args[0]) {
            last_status = run_command(args, environ, prog, lineno);
        }

        free_args(args);
        free(line);
    }

    /* IMPORTANT: return the last command status (checker expects 127) */
    return last_status;
}
