#include "main.h"

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread = getline(&line, &bufsize, stdin);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

char **parse_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= bufsize)
		{
			char **tmp = realloc(tokens, (bufsize + 64) * sizeof(char *));
			if (!tmp)
			{
				free(tokens);
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			tokens = tmp;
			bufsize += 64;
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

void free_array(char **array)
{
	free(array);
}
