#include "shell.h"

/**
  * leading_slash_in_path - Checks if file starts with "/"
  * @str: The filename to be checked
  *
  * Return: 0 if Yes and 1 if No
  */

int leading_slash_in_path(const char *str)
{
	if (str == NULL || *str != '/')
	{
		return (0);
	}
	return (1);
}

/**
 * find_executable_path - Get the executable path of file
 * @path: Full path variable
 * @file_name: The executable file
 *
 * Return: Full path of executable file
 */

char *find_executable_path(char *path, char *file_name)
{
	char *path_copy, *token;
	struct stat file_path;
	char *path_buffer = NULL;

	if (strncmp(file_name, "./", 2) == 0)
	{
		if (stat(file_name, &file_path) == 0 && access(file_name, X_OK) == 0)
		{
			return (strdup(file_name));
		}
		else
		{
			return (NULL);
		}
	}

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		if (path_buffer)
		{
			free(path_buffer);
			path_buffer = NULL;
		}
		path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
		if (!path_buffer)
		{
			perror("Error: malloc failed");
			exit(EXIT_FAILURE);
		}
		strcpy(path_buffer, token);
		strcat(path_buffer, "/");
		strcat(path_buffer, file_name);
		strcat(path_buffer, "\0");

		if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
		{
			free(path_copy);
			return (path_buffer);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	if (path_buffer)
		free(path_buffer);
	return (NULL);
}

/**
 * get_file_path - Gets the full path of the file
 * @file_name: Argument name
 *
 * Return: The full path argument to the file
 */

char *get_file_path(char *file_name)
{
	char *path = NULL;
	char *full_path;
	char *shell_name = "./hsh";
	int i = 0;

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = &environ[i][5];
			break;
		}
		i++;
	}
	if (leading_slash_in_path(file_name) && access(file_name, X_OK) == 0)
		return (strdup(file_name));
	if (!path)
	{	
		write(2, shell_name, strlen(shell_name));
		write(2, ": 1: ", 5);
		write(2, file_name, strlen(file_name));
		write(2, ": not found\n", 12);
		return (NULL);
	}
	full_path = find_executable_path(path, file_name);

	if (full_path == NULL)
	{
		write(2, shell_name, strlen(shell_name));
		write(2, ": 1: ", 5);
		write(2, file_name, strlen(file_name));
		write(2, ": not found\n", 12);

		return (NULL);
	}
	return (full_path);
}

