#include "shell.h"

/**
 * shell_no_interactive - command line interpreter
 *
 * Return: void
 */

void shell_no_interactive(void)
{
	char *input;
	char **args;
	int status = -1;

	do {
		input = read_stream();
		args = tokenize_input(input);
		status = execute_commands(args);

		free(input);
		free(args);

		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}

