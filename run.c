#include "main.h"

extern char **environ;

/**
 * run_command - resolve + execute a command (no fork if not found)
 * @args:   NULL-terminated argv
 * @env:    envp or NULL to use global environ
 * @prog:   program name for errors (e.g., "./hsh")
 * @lineno: 1-based input line number for errors
 *
 * Return: child's exit status, or 127 if not found, or small non-zero on error
 */
int run_command(char **args, char **env, const char *prog, int lineno)
{
    char *cmd_path;
    pid_t pid;
    int status = 0;
    char **envp = env ? env : environ;

    if (!args || !args[0])
        return 0;

    /* Do NOT handle "exit" here; main() handles it to free memory first */

    /* Resolve first; do NOT fork if not found */
    cmd_path = find_path(args[0], envp);
    if (!cmd_path) {
        fprintf(stderr, "%s: %d: %s: not found\n",
                prog ? prog : "./hsh", lineno, args[0]);
        return 127;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(cmd_path);
        return (errno ? errno : 1);
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

    if (WIFEXITED(status))   return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return 1;
}
