#include "shell.h"

/**
 * find_path - Locates the full path of a command
 * @cmd: Command to find
 * @env: Environment variables
 *
 * Return: Full path to command or NULL if not found
 */
char *find_path(char *cmd, char **env)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	path = _getenv("PATH", env);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
			return (NULL);

		sprintf(full_path, "%s/%s", dir, cmd);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
