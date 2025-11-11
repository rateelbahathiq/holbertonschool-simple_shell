/* shell.h */
#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Limits */
#define MAX_ARGS 128


void display_prompt(void);
char *read_line(void);
char **parse_line(char *line);
void free_array(char **array);


int   run_command(char **args, char **env);
char *find_path(char *command, char **env);

char *_getenv(const char *name, char **env);
int   _strcmp(const char *s1, const char *s2);

#endif /* SHELL_H */
