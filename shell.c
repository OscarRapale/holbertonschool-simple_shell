#include "shell.h"

/**
 * main - Entry point and main loop of shell
 *
 * Return: 0 on success
 */

int main(void)
{
	char *line;
	char **array;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("\nuser@simple_shell$ ");

		line = read_input();
		array = tokenize_input(line);

		if (strcmp(array[0], "exit") == 0)
		{
			free(line);
			free(array);
			exit(0);
		}
		if (strcmp(array[0], "env") == 0)

		{

			env(array);

			free(line);

			free(array);

			continue;

		}
		create_process(array[0], array);

		free(line);
		free(array);
	}

	return (0);
}
