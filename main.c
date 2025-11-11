#include "main.h"

extern char **environ;

int main(int ac, char **av)
{
    char *line = NULL;
    char **args = NULL;
    int lineno = 0;
    int last_status = 0;
    const char *prog = (av && av[0]) ? av[0] : "./hsh";

    (void)ac;

    while (1)
    {
        display_prompt();

        line = read_line(); /* NULL on EOF */
        if (!line) {
            if (isatty(STDIN_FILENO)) write(STDOUT_FILENO, "\n", 1);
            break;
        }

        lineno++;

        args = parse_input(line);
        if (args && args[0]) {
            /* Built-in: exit (no args) — keep last_status; don't reset it */
            if (strcmp(args[0], "exit") == 0) {
                free_args(args);
                free(line);
                break;              /* exit with whatever last_status currently is */
            }

            last_status = run_command(args, environ, prog, lineno);
        }

        free_args(args);
        free(line);
    }

    return last_status;  /* this will be 2 for the failing ls case */
}
