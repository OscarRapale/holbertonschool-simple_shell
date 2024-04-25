#include "shell.h"

/**
  * read_input - Reads the input from the users
  *
  * Return: Character variable to the program
  */

char *read_input(void)
{
	char *buffer;
	size_t buf_size;
	ssize_t nread;

	buffer = NULL;
	buf_size = 0;
	nread = getline(&buffer, &buf_size, stdin);

	if (nread == -1)
	{
		free(buffer);
		exit(0);
	}

	buffer = handle_symbols(buffer);

	return (buffer);
}


/**
  * execute_command - Executes the input from the buffer
  * @input: The argument from the buffer
  * @argv: Array of argument
  * @env: Environment variables
  * @shell_data: exit status code
  *
  */

void execute_command(char *input, char *argv[], char **env,
		shell_data_t *shell_data)
{
	char *args[10];
	char *path, *shell_name;
	int status, num_args, i;
	pid_t child_pid;

	shell_name = argv[0];
	num_args = tokenize_input(input, args);

	if (num_args == 0)
		return;
	if (builtin_commands(args, num_args, env) == 1)
		return;

	if (strcmp(args[0], "exit") == 0)
	{
		free(input);
		shell_exit(args, shell_data);
		return;
	}

	path = get_file_path(args[0]);
	if (path == NULL)
	{
		free(input);
		for (i = 1; i < num_args; i++)
		{
			free(args[i]);
		}
		args[0] = NULL;
    	exit(127);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Failed to create");
		free(input);
		free(path);
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			write(2, shell_name, strlen(shell_name));
    		write(2, ": 1: ", 5);
    		write(2, args[0], strlen(args[0]));
    		write(2, ": not found\n", 12);
			free(input);
			free(path);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			shell_data->last_exit_status = WEXITSTATUS(status);
	}
	free(path);
}

/**
  * tokenize_input - Tokenizes the input strings
  * @input: Argument input
  * @args: The array of strings
  *
  * Return: Number of the items tokenized
  */

int tokenize_input(char *input, char *args[])
{
	int count;
	char *token;

	count = 0;
	token = strtok(input, " \n");

	while (token)
	{
		args[count] = token;
		token = strtok(NULL, " \n");
		count++;
	}

	args[count] = NULL;
	return (count);
}

/**
  * builtin_commands - Handle all the built in commands
  * @args: Arguments to the built in commands
  * @num_args: Number of argument
  * @env: The environment variables
  *
  * Return: 1 if successful, 0 if unsuccessful
  */

int builtin_commands(char **args, int num_args, char **env)
{
	if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args, num_args);
		return (1);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env(env);
		return (1);
	}
	return (0);
}

/**
  * handle_symbols - Handles the '#' in the input
  * @input: Input value
  *
  * Return: The stripped down input
  */

char *handle_symbols(char *input)
{
	char *comment_pos;

	comment_pos = strstr(input, " #");

	if (comment_pos)
	{
		*comment_pos = '\0';
	}

	return (input);
}
