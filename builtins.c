#include "main.h"

/**
 * handle_env - Prints the environment variables.
 */
void handle_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
		printf("%s\n", *env);
}

/**
 * handle_exit - Exits the shell.
 */
void handle_exit(void)
{
	exit(0);
}

