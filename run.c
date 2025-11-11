#include "main.h"

extern char **environ;

int run_command(char **args, char **env, const char *prog, int lineno)
{
    char *cmd_path;
    pid_t pid;
    int status = 0;
    char **envp = env ? env : environ;

    if (!args || !args[0])
        return 0;

    /* minimal built-in: exit (no args) */
    if (_strcmp) {
        if (_strcmp(args[0], "exit") == 0) exit(0);
    } else {
        if (strcmp(args[0], "exit") == 0) exit(0);
    }

    /* Resolve first: if not found, print EXACT required format and return 127 */
    cmd_path = find_path(args[0], envp);
    if (!cmd_path)
    {
        /* EXACT format: "<prog>: <lineno>: <cmd>: not found\n" */
        fprintf(stderr, "%s: %d: %s: not found\n", prog, lineno, args[0]);
        return 127; /* DO NOT fork */
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(cmd_path);
        return errno ? errno : 1;
    }

    if (pid == 0) {
        execve(cmd_path, args, envp);
        perror("execve");
        _exit(127);
    }

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        free(cmd_path);
        return 1;
    }

    free(cmd_path);

    /* Normalize child's status to an exit code */
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);
    return 1;
}
