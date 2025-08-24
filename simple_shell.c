#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char input[MAX_INPUT];
	char *argv[2];
	pid_t pid;
	int status;
	size_t len;

	while (1)
	{
		if (fgets(input, MAX_INPUT, stdin) == NULL)
		{
			/* Handle Ctrl+D (EOF) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove newline character */
		len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
			input[len - 1] = '\0';

		if (input[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			argv[0] = input;
			argv[1] = NULL;

			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
