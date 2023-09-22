#include "shell.h"

/**
 * _strlen - length of string
 * @str: string
 *
 * Return: int
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - string comparison
 * @str1: string 1
 * @str2: string 2
 *
 * Return: 0 if OK, int if KO
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _strstart - checks if a string starts with a string
 * @str: string
 * @del: substring
 *
 * Return: string or NULL
 */
char *_strstart(const char *str, const char *del)
{
	while (*del)
		if (*del++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat - concatenates two strings
 * @d: the first string
 * @s: the second string
 *
 * Return: string
 */
char *_strcat(char *d, char *s)
{
	char *res = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (res);
}
