#include "shell.h"

/**
 * execute_commands - checks if command is a builtin or process
 * @args: command and its flags
 *
 * Return: 1 on success, 0 otherwise
 */

int execute_commands(char **args)
{
	char *builtin_func_list[] = {
		"cd",
		"exit",
		"env",
		"help"
	};
	int (*builtin_func[])(char **) = {
		&my_cd,
		&my_exit,
		&my_env,
		&my_help
	};
	size_t i = 0;

	if (args[0] == NULL)
	{
		return (-1);
	}

	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (new_process(args));
}

