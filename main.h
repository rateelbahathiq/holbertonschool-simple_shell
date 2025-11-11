#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/* Environment variable */
extern char **environ;
/* Limits */
#define MAX_ARGS 128

/* Main shell functions */
void display_prompt(void);
char *read_line(void);
char **parse_input(char *line);
void  free_args(char **args);
void free_array(char **array);

/* Path and execution functions */
char *get_path_env(void);
char *check_absolute_path(char *command);
char *search_in_path(char *command, char *path_env);
int execute_command(char **args, char *argv0, char *line, int last_status);
int fork_and_execute(char *command_path, char **args, char *argv0);

/* Built-in command functions */
void handle_exit(char *line, char **args, int status);
int handle_env(void);
int is_builtin(char **args, char *line, int status);

int   run_command(char **args, char **env);
char *find_path(char *command, char **env);

char *_getenv(const char *name, char **env);
int   _strcmp(const char *s1, const char *s2);

#endif /* MAIN_H */
