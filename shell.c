#include "shell.h"

/**
 * main - Entry point and main loop of shell
 *
 * Return: 0 on success
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
<<<<<<< HEAD
		shell_interactive();
	}
	else
	{
		shell_no_interactive();
=======
		if (isatty(STDIN_FILENO))
			printf("\nuser@simple_shell$ ");

		buffer = read_input();
		array = tokenize_input(buffer);

		if (array == NULL)
		{
			free(buffer);
			continue;
		}

		if (strcmp(array[0], "exit") == 0)
		{
			free(buffer);
			free(array);
			exit(0);
		}
		if (strcmp(array[0], "env") == 0)
		{
			env(array);
			continue;
		}
		path = get_file_path(array[0]);

		create_process(path, array);

		free(buffer);
		free(array);
>>>>>>> main
	}
	return (0);
}

