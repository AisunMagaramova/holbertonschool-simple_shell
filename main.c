#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    ssize_t nread;
    size_t len = 0;
    char *line = NULL;
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");
        nread = getline(&line, &len, stdin);

        if (nread == -1) /* EOF or error */
        {
            putchar('\n');
            break;
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(line);
            exit(EXIT_FAILURE);
        }
        if (pid == 0) /* child */
        {
            char *args[2];
            args[0] = line;
            args[1] = NULL;
            execve(args[0], args, environ);
            /* if execve fails */
            perror("./shell");
            free(line);
            exit(EXIT_FAILURE);
        }
        else /* parent */
        {
            waitpid(pid, &status, 0);
        }
    }
    free(line);
    return (0);
}
