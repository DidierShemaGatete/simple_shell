#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$"

int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		printf("%s", PROMPT);
		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				putchar('\n');
				exit(EXIT_SUCCESS);
			}
			else
			{

				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		if (buffer[nread - 1] == '\n')
		{
			buffer[nread - 1] = '\0';
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);

		} else if (pid == 0)
		{
			/* child process firpid first*/
			execlp(buffer, buffer, NULL);
			/*IF we get here, the exec failed*/
			perror("execlp");

			exit(EXIT_FAILURE);
		} else
		{
			/*parent process*/
			do

			{
				pid_t wpid = waitpid(pid, &status, WUNTRACED);

				if (wpid == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}


	free(buffer);

	exit(EXIT_SUCCESS);
}
