#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - simple shell
 * Return: 0
 */
extern char **environ;
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
		printf("#cisfun$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		pid = fork();
		if (pid == 0)
		{
			char *args[] = {line, NULL};
			if (execve(line, args, environ) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0):
		}
		else
		{
			perror("fork");
		}
	}

	free(line);
	return 0;
}
