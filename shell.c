/* shell.c */
#include "shell.h"

extern char **environ;

int main(void)
{
	char *line = NULL;
	char **args = NULL;

	while (1)
	{
		display_prompt();

		line = read_line(); /* NULL on EOF */
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_line(line);    /* tokens reference 'line' */
		if (args && args[0])
			run_command(args, environ);

		free_array(args);           /* frees only the array */
		free(line);                 /* free owner buffer */
	}
	return (0);
}
