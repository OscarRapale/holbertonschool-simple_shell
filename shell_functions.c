#include "shell.h"

/**
 * read_input - Reads input from the user
 *
 * Return: A pointer to the buffer where the input is stored
 */

char *read_input(void)
{
	char *buffer = NULL;
	size_t n = 0;
	ssize_t read;

	read = getline(&buffer, &n, stdin);

	if (read == -1)
	{
		exit(0);
	}
	return (buffer);
}

/**
 * tokenize_input - Tokenizes the input into an array of strings
 * @buffer: The input to tokenize
 *
 * Return: A pointer to the array of strings
 */

char **tokenize_input(char *buffer)
{
	char *token;
	char **array;
	int i;

	token = strtok(buffer, " \n");

	array = malloc(sizeof(char *) * 1024);
	i = 0;
	while (token)
	{
		array[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * create_process - Creates a new process and executes the command
 * @path: The path to the executable
 * @array: The array of arguments
 */

void create_process(char *path, char **array)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Failed to create.");
		exit(41);
	}

	if (child_pid == 0)
	{
		if (execve(path, array, NULL) == -1)
		{
			exit(97);
		}
	}
	else
	{
		wait(&status);
	}
}

