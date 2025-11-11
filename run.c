#include "main.h"

extern char **environ;

/**
 * run_command - resolve + execute a command (0.2: no fork if not found)
 * @args:   NULL-terminated argv (args[0] is the command)
 * @env:    environment (envp) or NULL to use global environ
 * @prog:   program name to print in errors (e.g., av[0] or "./hsh")
 * @lineno: 1-based command line counter for error messages
 *
 * Return: exit status of the executed command,
 *         or 127 if command not found,
 *         or a small non-zero code on error.
 */
int run_command(char **args, char **env, const char *prog, int lineno)
{
	char *cmd_path;
	pid_t pid;
	int status = 0;
	char **envp = env ? env : environ;

	if (!args || !args[0])
		return (0);

	/* minimal built-in: exit (no args handling required for 0.2) */
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	/* 0.2: resolve first; do NOT fork if not found */
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		/* EXACT format required by checker */
		fprintf(stderr, "%s: %d: %s: not found\n",
		        prog ? prog : "./hsh", lineno, args[0]);
		return (127);
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
		/* Child: replace image */
		execve(cmd_path, args, envp);
		/* If execve returns, it's an error */
		perror("execve");
		_exit(127);
	}

	/* Parent: wait and normalize status */
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		free(cmd_path);
		return (1);
	}

	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
