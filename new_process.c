#include "shell.h"

/**
 * new_process - create a new process
 * @args: array of strings that contains the cmd and flags
 *
 * Return: 1 if succes, 0 otherwise
 */

int new_process(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) ==  -1)
		{
			if (errno == ENOENT)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				exit(127);
			}
		}
		else
		{
			perror("error with child process");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("error with process: forking");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

