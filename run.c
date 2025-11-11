#include "main.h"

extern char **environ;

/**
 * run_command - resolves and executes commands
 * @args:   array of arguments
 * @env:    environment (envp)
 * @prog:   program name (e.g., "./hsh")
 * @lineno: current line number for error messages
 *
 * Return: exit status (0 on success, 127 if not found, or child status)
 */
int run_command(char **args, char **env, const char *prog, int lineno)
{
	char *cmd_path;
	pid_t pid;
	int status = 0;
	char **envp = env ? env : environ;

	if (!args || !args[0])
		return (0);

	/* ✅ Built-in: exit (no args) */
	if (strcmp(args[0], "exit") == 0)
	{
		/* Optional: free args or other globals if needed */
		exit(0);
	}

	/* Resolve path — don’t fork if not found */
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
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
		/* child process */
		execve(cmd_path, args, envp);
		perror("execve");
		_exit(127);
	}

	/* parent process */
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
