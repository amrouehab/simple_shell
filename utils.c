#include "main.h"

/**
 * execute_command - Executes a command.
 * @args: The arguments for the command.
 */
void execute_command(char **args)
{
	char *command = find_command(args[0]);

	if (command == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}

	if (execve(command, args, environ) == -1)
		perror(args[0]);

	exit(EXIT_FAILURE);
}

/**
 * find_command - Searches for a command in the PATH.
 * @command: The command to find.
 *
 * Return: The full path to the command or NULL if not found.
 */
char *find_command(char *command)
{
	struct stat st;
	char *path = getenv("PATH");
	char *dir;
	static char full_path[1024];

	if (stat(command, &st) == 0)
		return command;

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
			return full_path;
		dir = strtok(NULL, ":");
	}

	return NULL;
}

/**
 * parse_input - Parses the input into arguments.
 * @line: The input line.
 *
 * Return: An array of arguments.
 */
char **parse_input(char *line)
{
	static char *args[100];
	int i = 0;

	args[i] = strtok(line, " ");
	while (args[i] != NULL)
		args[++i] = strtok(NULL, " ");

	return args;
}

