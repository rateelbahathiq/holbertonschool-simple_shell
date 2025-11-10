#include "shell.h"

extern char **environ;

/**
 * simple_shell - Simple UNIX command line interpreter
 *
 * Description:
 * Displays a prompt and waits for the user to type a command.
 * Executes only one-word commands (no arguments).
 * If command not found, prints an error message.
 * Handles end-of-file (Ctrl+D).
 *
 * Return: Nothing
 */
void simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *argv[2]; /* Command + NULL terminator */

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
			free(line);
			exit(1);
		}

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, environ) == -1)
				perror("./shell");
			exit(1);
		}
		else
			wait(&status);
	}
}
