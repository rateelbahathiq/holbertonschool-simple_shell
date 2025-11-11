#include "main.h"

extern char **environ;

int run_command(char **args, char **env, const char *prog, int lineno)
{
    char *cmd_path;
    pid_t pid;
    int status = 0;
    char **envp = env ? env : environ;
    int i;

    if (!args || !args[0])
        return 0;

    /* ✅ Built-in: exit */
    if (strcmp(args[0], "exit") == 0)
        exit(0);

    /* ✅ Built-in: env */
    if (strcmp(args[0], "env") == 0)
    {
        for (i = 0; envp[i]; i++)
        {
            write(STDOUT_FILENO, envp[i], strlen(envp[i]));
            write(STDOUT_FILENO, "\n", 1);
        }
        return 0; /* success */
    }

    /* PATH lookup */
    cmd_path = find_path(args[0], envp);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: %d: %s: not found\n",
                prog ? prog : "./hsh", lineno, args[0]);
        return 127;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        return (errno ? errno : 1);
    }

    if (pid == 0)
    {
        execve(cmd_path, args, envp);
        perror("execve");
        _exit(127);
    }

    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        free(cmd_path);
        return 1;
    }

    free(cmd_path);

    if (WIFEXITED(status))   return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return 1;
}
