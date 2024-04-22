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
	char **array;
	int i = 0;
	int j = 0;
	int word_count = 0;

	while (line[i] != '\0')

    {
	    if (line[i] == ' ')

        {
		i++;
		continue;

        }
	word_count++;
	while (line[i] != ' ' && line[i] != '\0')

        {
		i++;

        }

    }
	array = malloc(sizeof(char *) * (word_count + 1));
	if (array == NULL)

	{
		return NULL;

	}
	i = 0;
	j = 0;
	while (line[i] != '\0')

	{
		if (line[i] == ' ')

		{
			i++;
			continue;

		}
		int word_length = 0;
		while (line[i] != ' ' && line[i] != '\0')

		{
			word_length++;
			i++;

		}
		array[j] = malloc(sizeof(char) * (word_length + 1));
		if (array[j] == NULL)
		{
			free(array);
			return NULL;
		}
		int k = 0;
		while (k < word_length)

		{
			array[j][k] = line[i - word_length + k];
			k++;
		}
		array[j][k] = '\0';
		j++;
		i++;
	}

	array[j] = NULL;
	free(array);
	return array;

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

/**
 * env - Prints the current environment
 *
 * @array: Array of arguments passed to the function
 */


void env(char **array)

{

	int i;


	if (array == NULL)

		return;


	for (i = 0; environ[i] != NULL; i++)

		printf("%s\n", environ[i]);

}
