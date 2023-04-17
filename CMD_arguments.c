#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	char *token;
	char *argv[10];
	int i, status;
	pid_t pid;

	while (1)
	{
		printf("#cisfun$");
		nread = getline(&buffer, &bufsize, stdin);

		if (nread == -1)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		token = strtok(buffer, " ");

		i = 0;

		while (token != NULL)

		{

			argv[i++] = token;

			token = strtok(NULL, " ");

		}

		argv[i] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}

	free(buffer);

	return (EXIT_SUCCESS);
}
