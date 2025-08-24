#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_INPUT 1024

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
            break;

        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t'))
        {
            input[len - 1] = '\0';
            len--;
        }

        argv[0] = input;
        argv[1] = NULL;

        pid = fork();
        if (pid == 0)
        {
            execve(argv[0], argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
