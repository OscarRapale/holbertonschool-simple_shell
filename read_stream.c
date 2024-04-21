#include "shell.h"

/**
 * read_stream - read input from stream
 *
 * Return: pointer that points to input
 */

char *read_stream(void)
{
	int bufsize = 1024;
	int i = 0;
	char *input = malloc(sizeof(char) * bufsize);
	int character;

	if (input == NULL)
	{
		fprintf(stderr, "allocation error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		character = getchar();
		if (character == EOF)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			input[i] = '\0';
			return (input);
		}
		else
		{
			input[i] = character;
		}
		i++;
		if (i >= bufsize)
		{
			bufsize += bufsize;
			input = realloc(input, bufsize);
			if (input == NULL)
			{
				fprintf(stderr, "reallocation error");
				exit(EXIT_FAILURE);
			}
		}
	}
}

