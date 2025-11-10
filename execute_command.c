#include "shell.h"

/**
 * execute_command - Executes user commands
 * @args: Parsed arguments
 * @av: Program name and arguments
 * @env: Environment variables
 *
 * Return: Nothing
 */
void execute_command(char **args, char **av, char **env)
{
	pid_t pid;
	int status;
	char *command_path;

	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(EXIT_SUCCESS);
	}

	command_path = find_path(args[0], env);
	if (!command_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command_path, args, env) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);

	free(command_path);
}
