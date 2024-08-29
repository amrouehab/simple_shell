#include "main.h"

/**
 * main - Entry point for the simple shell
 * 
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	char **args;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			perror("getline");
			break;
		}

		/* Remove the newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Parse the command */
		args = parse_input(line);
		if (args[0] == NULL)
			continue;

		/* Handle built-in commands */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			handle_exit();
		}
		if (strcmp(args[0], "env") == 0)
		{
			handle_env();
			continue;
		}

		/* Fork and execute the command */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			/* Child process */
			execute_command(args);
		}
		else
		{
			/* Parent process */
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	free(line);
	return 0;
}

