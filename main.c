#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    prompt_loop();

    return (0);
}
