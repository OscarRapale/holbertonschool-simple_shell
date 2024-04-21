#include "shell.h"

/**
 * shell_interactive - Command line interpreter
 *
 * Return: void
 */

void shell_interactive(void)
{
	char *input;
	char **args;
	int status = -1;

	do {
		printf("user@simple_shell$ ");
		input = read_input();
		args = tokenize_input(input);
		status = execute_commands(args);

		free(input);
		free(args);

		if (status == 0)
		{
			exit(status);
		}
	} while (status != 0);
}
