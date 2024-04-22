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
			printf("\nuser@simple_shell$ ")

			line = read_input();
		if (line == NULL)
		{
			free(line);
			break;
		}

		array = tokenize_input(line);
		if (array == NULL)
		{
			free(line);
			continue;
		}

		if (strcmp(array[0], "exit") == 0)
		{
			free(line);
			free(array);
			break;
		}

		if (execve(array[0], array, environ) == -1)
		{
			perror("Error: ");
			free(line);
			free(array);
			continue;
		}
	}

	return (0);
}
