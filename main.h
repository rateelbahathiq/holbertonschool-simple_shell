#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* prompt / IO */
void display_prompt(void);
char *read_line(void);

/* parsing */
char **parse_input(char *line);
void  free_args(char **args);

/* PATH + exec */
char *find_path(char *command, char **env);

/* run a command, print errors using prog/lineno, and return its exit status */
int   run_command(char **args, char **env, const char *prog, int lineno);

/* optional utils (only if used) */
char *_getenv(const char *name, char **env);
int   _strcmp(const char *s1, const char *s2);

#endif /* MAIN_H */
