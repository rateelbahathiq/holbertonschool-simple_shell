#include "shell.h"

/**
 * _getenv - Retrieves an environment variable's value
 * @name: Name of the variable
 * @env: Environment variables
 *
 * Return: Value of environment variable or NULL if not found
 */
char *_getenv(const char *name, char **env)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}
