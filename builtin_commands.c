#include "shell.h"

/**
 * my_exit - exit the shell
 * @args: list of arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int my_exit(char **args)
{
	int status = 0;
	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}
	else
	{
		status = 127;
	}
	exit(status);
	return (1);
}

/**
 * my_cd - change directories
 * @args: list of arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int my_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Expected argument to \"cd\"\n");
		return (1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Error");
			return (1);
		}
	}
	return (1);
}

/**
 * my_env - prints the environment
 * @args: list of arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int my_env(char **args)
{
	char **env = environ;
	char *value;

	if (args[1] != NULL)
	{
		value = getenv(args[1]);
		if (value == NULL)
		{
			fprintf(stderr, "env: %s not found\n", args[1]);
			return (1);
		}
		else
		{
			printf("%s=%s\n", args[1], value);
			return (1);
		}
	}
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}

	return (1);
}

/**
 * my_help - display help message
 * @args: list of arguments
 *
 * Return: 1 on success, 0 otherwise
 */

int my_help(char **args)
{
	if (args[1] == NULL)
	{
		printf("Type 'help name' to find out more about the function 'name'.\n");
		return (1);
	}

	if (strcmp(args[1], "cd") == 0)
	{
		printf("cd [directory] - Change the current directory to [directory]\n");
	}
	else if (strcmp(args[1], "env") == 0)
	{
		printf("env [name] - Print the value of the environment variable [name]\n");
	}
	else if (strcmp(args[1], "help") == 0)
	{
		printf("help [command] - Display help for [command], or general help if no command is given\n");
	}
	else if (strcmp(args[1], "exit") == 0)
	{
		printf("exit [status] - Exit the shell with optional exit status\n");
	}
	else
	{
		fprintf(stderr, "Unknown command: %s\n", args[1]);
		return (1);
	}
	return (1);
}

