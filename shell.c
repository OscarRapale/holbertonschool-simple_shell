#include "shell.h"

/**
 * main - Entry point and main loop of shell
 *
 * Return: 0 on success
 */

int main(void)
{
	char *buffer;
	char **array;
	char *path;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("\nuser@simple_shell$ ");

		buffer = read_input();
		array = tokenize_input(buffer);
		path = get_file_path(array[0]);

		create_process(path, array);

		free(buffer);
		free(array);
	}
	return (0);
}

