/* path.c */
#include "shell.h"

/* Optional custom strcmp; you may use strcmp instead */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2)) { s1++; s2++; }
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/* getenv using provided env (envp) */
char *_getenv(const char *name, char **env)
{
	size_t nlen = strlen(name);
	int i;

	if (!name || !env)
		return (NULL);

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], name, nlen) == 0 && env[i][nlen] == '=')
			return (env[i] + nlen + 1);
	}
	return (NULL);
}

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

/* Return malloc'd absolute path or NULL if not found */
char *find_path(char *command, char **env)
{
	char *pathval, *paths, *dir, *savep = NULL, *full;

	if (!command || !*command)
		return (NULL);

	/* If command contains '/', treat as a path directly */
	if (strchr(command, '/'))
		return (is_executable_file(command) ? strdup(command) : NULL);

	pathval = _getenv("PATH", env);
	if (!pathval || !*pathval)
		return (NULL);

	paths = strdup(pathval);
	if (!paths)
		return (NULL);

	for (dir = strtok_r(paths, ":", &savep); dir; dir = strtok_r(NULL, ":", &savep))
	{
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
			return (full);
		}
		free(full);
	}

	free(paths);
	return (NULL);
}
