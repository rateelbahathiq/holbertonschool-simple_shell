#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>     /* NULL */
#include <sys/types.h>  /* pid_t */

/* Function prototypes */
char **parse_input(char *line);
int run_command(char **args, char **av, char **env);
char *find_path(char *command, char **env);
int _strcmp(const char *s1, const char *s2);
void free_args(char **args);

#endif /* SHELL_H */
