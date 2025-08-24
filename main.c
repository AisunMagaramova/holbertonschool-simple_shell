#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_INPUT 1024

int main(void)
{
    char input[MAX_INPUT];
    char *newline;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");  /* Prompt */

        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            /* Handle Ctrl+D */
            printf();
            break;
        }

        newline = strchr(input);
        if (newline)
            *newline = '\0';

        if (strlen(input) == 0)
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            char *argv[2];
            argv[0] = input;
            argv[1] = NULL;

            if (execve(input, argv, environ) == -1)
            {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
