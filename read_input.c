#include "shell.h"

/**
 * read_input - read input from stdin
 *
 * Return: pointer that points to a string
 * with the input content
 */

char *read_input(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	if (getline(&input, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input);
			perror("error while reading the input from stdin");
			exit(EXIT_FAILURE);
		}
	}
	return (input);
}
