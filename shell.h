#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char **parse_input(char *line);
void execute_command(char **args, char **av, char **env);
char *find_path(char *cmd, char **env);
void free_args(char **args);
char *_getenv(const char *name, char **env);
int _strcmp(char *s1, char *s2);

#endif /* SHELL_H */
