#ifndef SHELL_H
#define SHELL_H

#include <stddef.h> /* for NULL */

char **parse_input(char *line);
int run_command(char **args, char **env);
char *find_path(char *command, char **env);
char *_getenv(const char *name, char **env);
int _strcmp(const char *s1, const char *s2);
void free_args(char **args);

#endif /* SHELL_H */
