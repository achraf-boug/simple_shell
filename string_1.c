#include "shell.h"

/**
 * _strcpy - Copy a string to another.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string 'dest'.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strcpy2 - Create a duplicate of a string
 * @str: string to be duplicated
 *
 * Return: string, or NULL on failure
 */
char *_strcpy2(const char *str)
{
	int lg = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lg++;
	r = malloc(sizeof(char) * (lg + 1));
	if (!r)
		return (NULL);
	for (lg++; lg--;)
		r[lg] = *--str;
	return (r);
}

/**
 * _putstr - Print a string to stdout
 * @s: string
 *
 * Return: None.
 */
void _putstr(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - Write a character to stdout
 * @str: Character
 *
 * Return: 1 after writing
 */
int _putchar(char str)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}
