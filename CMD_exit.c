#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * Return: 0 on success
 */

int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		printf("$ ");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	}

	exit_shell(args); /* call exit_shell before exiting*/

	return (EXIT_SUCCESS);
}
