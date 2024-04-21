#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define TOK_DELIM " \t\r\n\a\""
extern char **environ;

/* Prototypes */
void shell_interactive(void);
void shell_no_interactive(void);
char *read_input(void);
char **tokenize_input(char *input);
int execute_commands(char **args);
int new_process(char **args);
char *read_stream(void);

/* Built-in functions */
int my_cd(char **args);
int my_exit(char **args);
int my_env(char **args);
int my_help(char **arg);

#endif /* SHELL_H */
