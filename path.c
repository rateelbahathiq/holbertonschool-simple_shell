#include "main.h"

/* Check that path is a regular file and executable */
static int is_executable_file(const char *path)
{
	struct stat st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	return (access(path, X_OK) == 0);
}

/* Join three strings a + b + c into a newly malloc'd buffer */
static char *join3(const char *a, const char *b, const char *c)
{
	size_t la = strlen(a), lb = strlen(b), lc = strlen(c);
	char *s = malloc(la + lb + lc + 1);

	if (!s)
		return (NULL);
	memcpy(s, a, la);
	memcpy(s + la, b, lb);
	memcpy(s + la + lb, c, lc);
	s[la + lb + lc] = '\0';
	return (s);
}

/**
 * find_path - Resolve a command name to an absolute path via PATH.
 * @command: Command name (e.g., "ls" or "/bin/ls")
 * @env:     Environment (envp)
 *
 * Return: malloc'd absolute path on success (caller must free), or NULL if not found.
 */
char *find_path(char *command, char **env)
{
	char *pathval, *paths, *dir, *full;

	if (!command || !*command)
		return (NULL);

	/* If command already contains '/', treat it as a path directly */
	if (strchr(command, '/'))
		return (is_executable_file(command) ? strdup(command) : NULL);

	/* Get PATH from provided environment */
	pathval = _getenv("PATH", env);
	if (!pathval || !*pathval)
		return (NULL);

	/* Duplicate PATH because strtok will modify the buffer */
	paths = strdup(pathval);
	if (!paths)
		return (NULL);

	/* Iterate directories separated by ':' using strtok (allowed) */
	for (dir = strtok(paths, ":"); dir; dir = strtok(NULL, ":"))
	{
		/* Empty entry in PATH means current directory */
		if (*dir == '\0')
			dir = ".";

		full = join3(dir, "/", command);
		if (!full)
		{
			free(paths);
			return (NULL);
		}

		if (is_executable_file(full))
		{
			free(paths);
			return (full); /* success, caller frees */
		}

		free(full);
	}

	free(paths);
	return (NULL); /* not found */
}
