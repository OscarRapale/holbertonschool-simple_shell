#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

extern char **environ;

/* Prototypes */

/* Shell Functions*/
int leading_slash_in_path(char const *str);
char *get_file_path(char *file_name);
char *find_executable_path(char *path, char *file_name);
void execute_command(char *input, char *argv[], char **env);
char *read_input(void);
int tokenize_input(char *input, char *args[]);
char *handle_symbols(char *input);

/* Built-in functions */
int builtin_commands(char **args, int num_args, char **env);
void print_env(char **env);
void handle_cd(char **args, int num_args);
void handle_exit(char *input, int exit_status);
void shell_exit(int status, bool is_exit_command);

#endif /* SHELL_H */
