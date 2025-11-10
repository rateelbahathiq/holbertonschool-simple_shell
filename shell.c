#include "main.h"

/**
	* display_prompt - Displays the shell prompt
	*
	* Return: void
	*/
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}

/**
	* read_line - Reads a line from stdin
	*
	* Return: Pointer to the line read, or NULL on EOF
	*/
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
	free(line);
	return (NULL);
	}

	if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	return (line);
}

/**
	* parse_line - Parses a line into arguments
	* @line: The line to parse
	*
	* Return: Array of arguments
	*/
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
	tokens[position] = token;
	position++;

	if (position >= bufsize)
	{
	bufsize += 64;
	tokens = realloc(tokens, bufsize * sizeof(char *));
	if (!tokens)
	{
	perror("realloc");
	exit(EXIT_FAILURE);
	}
	}

	token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
	* free_array - Frees an array of strings
	* @array: The array to free
	*
	* Return: void
	*/
void free_array(char **array)
{
	if (array)
	free(array);
}
