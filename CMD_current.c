#include "holberton.h"

/**
 * builtin_env - print the current environment
 * Return: 0 on success, -1 on failure
 */

int builtin_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		write(STDOUT_FILENO, environ[i], _strlen(environ[i])), write(STDOUT_FILENO, "\n" 1);

	return (0);

}
