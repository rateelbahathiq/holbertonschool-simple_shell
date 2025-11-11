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
            /* ✅ Built-in: exit (no args) — handle here so we can free first */
            if (strcmp(args[0], "exit") == 0) {
                free_args(args);
                free(line);
                last_status = 0;       /* per task: no arg handling, status 0 */
                break;                 /* clean exit with no leaks */
            }

            last_status = run_command(args, environ, prog, lineno);
        }

        free_args(args);
        free(line);
    }

    return last_status;
}
