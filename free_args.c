#include "shell.h"

/**
 * free_args - Frees memory allocated for arguments
 * @args: Array of argument strings
 *
 * Return: Nothing
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}
