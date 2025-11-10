#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		args = parse_input(line);
		if (args[0] != NULL)
			execute_command(args, av, env);

		free_args(args);
	}
	return (0);


}
