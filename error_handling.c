#include "shell.h"

/**
 * put_err - Print to stderr
 * @s: string to be printed
 *
 * Return: None
 */
void put_err(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		putchar_err(s[i]);
		i++;
	}
}

/**
 * putchar_err - Write a character to stderr
 * @str: Character to be written
 *
 * Return: 1 after writing
 */
int putchar_err(char str)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * putchar_file - Write a character to a file
 * @str: Character to be written
 * @file: File descriptor
 *
 * Return: 1 after writing
 */
int putchar_file(char str, int file)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(file, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * put_file - Write a string to a file
 * @str: string to be written
 * @file: File descriptor
 *
 * Return: Number of characters
 */
int put_file(char *str, int file)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putchar_file(*str++, file);
	}
	return (i);
}
