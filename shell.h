#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>     /* for size_t */
#include <stdio.h>      /* for printf, fprintf, perror, sprintf, stderr */
#include <stdlib.h>     /* for malloc, free, exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <string.h>     /* for strlen, strncmp, strtok, strdup */
#include <unistd.h>     /* for fork, execve */
#include <sys/types.h>  /* for pid_t */
#include <sys/wait.h>   /* for wait */
#include <sys/stat.h>   /* for struct stat, stat() */
/* Function prototypes */
int _strcmp(const char *s1, const char *s2);
void free_args(char **args);
char *find_path(char *cmd, char **env);
char *_getenv(const char *name, char **env);

#endif
