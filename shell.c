#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
extern char **environ;

/**
 * main - Simple Shell 0.1
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        /* Prompt */
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        /* Read input */
        nread = getline(&line, &len, stdin);

        if (nread == -1)
        {
            /* Handle Ctrl+D (EOF) */
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                break;
            }
            perror("getline");
            continue;
        }

        /* Remove newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Skip empty input */
        if (line[0] == '\0')
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            char *argv[] = {line, NULL};

            /* Try to execute command */
            if (execve(line, argv, environ) == -1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
