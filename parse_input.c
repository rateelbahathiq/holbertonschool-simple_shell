#include "shell.h"

/**
 * parse_input - Splits input string into arguments
 * @line: Input line from user
 *
 * Return: Array of argument strings
 */
char **parse_input(char *line)
{
	char *token, **args;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, " \t\r\n\a");
	}
	args[i] = NULL;
	return (args);
}
