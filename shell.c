#include "shell.h"

/**
  * main - main loop
  * @argc: Argumnt count
  * @argv: Array of arguments
  * @env: Environment variable
  *
  * Return: O Always succes
  */

int main(int argc, char *argv[], char **env)
{
	char *buffer;
	shell_data_t shell_data = {0};
	(void)argc;
	

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("user@simple_shell$ ");

		buffer = read_input();
		execute_command(buffer, argv, env, &shell_data);
		free(buffer);
	}

	return (0);
}
