#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_INPUT 1024

int main(void)
{
    char input[MAX_INPUT];
    pid_t pid;
    int status;
    size_t len;
    char *argv[2];

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            printf("\n");
            break;
        }

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

        if (pid == 0)
        {
            argv[0] = input;
            argv[1] = NULL;

            if (execve(input, argv, environ) == -1)
            {
                perror("Error");
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
