#include "shell.h"

/**
  * print_env - Prints the environment variables
  * @env: Arguments
  */

void print_env(char **env)
{
	while (*env != NULL)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

/**
  * handle_cd - Handles the cd functionality
  * @args: Array of commands
  * @num_args: Argument count
  */

void handle_cd(char **args, int num_args)
{
	const char *home_dir = NULL, *prev_dir = NULL;
	int i = 0;

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "HOME=", 5) == 0)
			home_dir = &environ[i][5];
		else if (strncmp(environ[i], "OLDPWD=", 7) == 0)
			prev_dir = &environ[i][7];
		i++;
	}

	if (num_args == 1 || strcmp(args[1], "~") == 0)
	{
		if (!home_dir)
		{
			perror("Home environment not set");
			return;
		}
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else if (num_args == 2 && strcmp(args[1], "-") == 0)
	{
		if (!prev_dir)
		{
			perror("OLDPWD environment not set");
			return;
		}
		if (chdir(prev_dir) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}

/**
  * handle_exit - Handles the exit functionality
  * @input: Input value to handle
  * @exit_status: Exit status of the code
  */

void handle_exit(char *input, int exit_status)
{
	free(input);
	exit(exit_status);
}

/**
  * shell_exit - Handles the exit status
  * @status: exit status code
  * @is_exit_command: boolian to execute exit when needed
  *
  * Return: Status of exit, 1 if otherwise
  */

void shell_exit(int status, bool is_exit_command)
{

	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		if (is_exit_command)
		{
			exit(exit_status);
		}
	}
	else
	{
		printf("Unknown termination condition\n");
		exit(1);
	}
}

