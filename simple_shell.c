#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

extern char **environ;

int main(void)
{
	char input[MAX_INPUT];
	pid_t pid;
	int status;
	char *argv[2];
	size_t len;

	while (1)
	{
		/* Yalnız interaktiv rejimdə prompt göstər */
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		/* İstifadəçi girişini oxu */
		if (fgets(input, MAX_INPUT, stdin) == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		/* Yeni sətrin (\n) silinməsi */
		len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
			input[len - 1] = '\0';

		/* Boş daxilolmanı keç */
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

			if (execve(argv[0], argv, environ) == -1)
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

	return 0;
}
