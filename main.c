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
    if (nread == -1)  // EOF və ya error
    {
        printf("\n");
        free(line);
        exit(EXIT_SUCCESS);
    }

    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    if (strlen(line) == 0)
        continue;  // boş sətir olduqda promptu yenidən göstər

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(line);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        char *args[] = {line, NULL};
        if (execve(args[0], args, environ) == -1)
        {
            perror("./shell");
            free(line);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}
