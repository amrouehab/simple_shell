#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

/* Function Prototypes */
void execute_command(char **args);
char *find_command(char *command);
void handle_env(void);
void handle_exit(void);
char **parse_input(char *line);

#endif /* MAIN_H */

