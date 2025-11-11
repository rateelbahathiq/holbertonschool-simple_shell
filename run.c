/* run.c */
#include "shell.h"

extern char **environ;

int run_command(char **args, char **env)
{
	char *cmd_path;
	pid_t pid;
	int status = 0;
	char **envp = env ? env : environ;

	if (!args || !args[0])
		return (0);

	/* minimal built-in: exit (no args) */
	if (_strcmp(args[0], "exit") == 0)
		exit(0);

	/* 0.2: resolve first; do NOT fork if not found */
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		dprintf(STDERR_FILENO, "%s: not found\n", args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (errno);
	}
	if (pid == 0)
	{
		execve(cmd_path, args, envp);
		perror("execve");
		_exit(127);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	return (status);
}
