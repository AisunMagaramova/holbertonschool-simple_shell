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
        /* Yalnız terminaldan daxil olduqda prompt göstər */
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout);
        }

        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            /* Ctrl+D basıldıqda çıxış */
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        /* Yeni sətri sil */
        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        if (input[0] == '\0')  /* boş sətir, keç */
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child prosesi: execve ilə işlət */
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
            /* Parent: child-ı gözləyir */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
