#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_LINE 256

extern char **environ;

/* Prototypes */
char *read_input(void);
char **tokenize_input(char *buffer);
void create_process(char *path, char **array);
int leading_slash_in_path(const char *str);
char *get_executable_path(char *path, char *file_name);
char *get_file_path(char *file_name);
void env(char **array);
#endif /* SHELL_H */
