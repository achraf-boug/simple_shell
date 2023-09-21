#include "shell.h"

/**
 * executeCMD - execute the commands
 * @command: command to execute
 * @argv: list of arguments
 * @envp: env params
 *
 * Return: void
 */
void executeCMD(char *command, char *argv[], char *envp[])
{
		pid_t pid;
		int status;
		/*Fork a child process*/
		pid = fork();

		if (pid == -1)
			perror("Error fork");
		else if (pid == 0)
		{
			/*Child process*/
			if (access(command, X_OK) == 0)
			{
				if (execve(command, argv, envp) == -1)
				{
					perror(command);
					_exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("%s: No such file or directory\n", command);
				_exit(EXIT_FAILURE);
			}
		}
		else
		{
			/*Parent process*/
			if (waitpid(pid, &status, 0) == -1)
				perror("waitpid");
		}
}

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

	while (1)
	{
		printf("($) ");
		fflush(stdout);

		chars = getline(&buffer, &bufsize, stdin);
		if (chars == -1)
		{
			/*Handle the "end of file" condition*/
			printf("\n");
			break;
		}

		/*Remove '\n'*/
		if (chars > 0 && buffer[chars - 1] == '\n')
			buffer[chars - 1] = '\0';
		else
		{
			printf("Error reading input!\n");
			exit(EXIT_FAILURE);
		}
		executeCMD(buffer, argv, envp);
	}

	free(buffer);
	return (argc);
}
