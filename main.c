#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	char *argv[2];
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			write(1, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		
		if (line[0] == '\0')
			continue;
		
		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	return (0);
}
