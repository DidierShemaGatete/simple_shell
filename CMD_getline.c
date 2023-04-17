#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _getline - reads an entire line from a file descriptor
 * @lineptr: pointer to the buffer containing the line
 * @n: size of the buffer
 * @stream: file descriptor to read from
 *
 * Return: the number of characters read, or -1 on failure
 */

ssize_t _getline(char **lineptr, size_t *n, int stream)
{
	static char buffer[1024];
	static char *buf_pos;
	ssize_t n_read = 0;
	ssize_t total_read = 0;

	if (!lineptr || !n)
		return (-1);
	/* Allocate buffer if it doesn't exist or if the requested size is larger */
	if (*lineptr == NULL || *n == 0)
	{
		*n = 120;
		*lineptr = malloc(*n);

		if (!*lineptr)
			return (-1);
	}

	/* Read from stdin in chunks */

	while ((n_read = read(stream, buffer, 1024)) > 0)
	{
		/* loop through each character int the buffer*/
		for (ssize_t i = 0; i < n_read; i++)
		{
			/*if the buffer is full. resize it*/
			if (total_read >= *n - 1)
			{
				*n * = 2;
				*lineptr = realloc(*lineptr);
				if (!*lineptr)
					return (-1);

			}

			/* Store the character in the buffer */
			(*lineptr)[total_read++] = buffer[i];

			/* If we've reached the end of a line, retur */
			if (buffer[i] == '\n')
			{
				(*lineptr)[total_read] = '\0';
				return (total_read);
			}
		}

		/* Update buf_pos to the next character in the buffer*/
		buf_pos = buffer + n_read;
	}

	/* If read failed or we didn't read anything, return -1 */
	if (n_read == -1 || total_read == 0)
		return (-1);
	/* Add null terminator to the end of the string*/
	(*lineptr)[total_read] = '\0';

	return (total_read);
}
