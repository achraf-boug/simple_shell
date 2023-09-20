#include "shell.h"

/**
 * main - run shell
 * @argc: number of arguments
 * @argv: list of arguments
 * @envp: env params
 *
 * Return: argc
 */
int main(int argc, char *argv[], char *envp[])
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t chars;

	argv[0] = "hsh";
	envp[0] = "envp";
	while (1)
	{
		printf("(Gx Shell)$ ");
		fflush(stdout);

		chars = getline(&buffer, &bufsize, stdin);
		if (chars > 0 && buffer[chars - 1] == '\n')
			buffer[chars - 1] = '\0';
		else
		{
			printf("Error reading input!\n");
			exit(EXIT_FAILURE);
		}
	}

	free(buffer);
	return (argc - 1);
}
