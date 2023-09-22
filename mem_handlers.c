#include "shell.h"

/**
 **setMem - fills memory with bytes
 *@p: pointer
 *@b: byte
 *@nb: nbr of bytes
 *Return: pointer
 */
char *setMem(char *p, char b, unsigned int nb)
{
	unsigned int i;

	for (i = 0; i < nb; i++)
		p[i] = b;
	return (p);
}

/**
 * flush_list_str - flush array of string
 * @str: string
 */
void flush_list_str(char **str)
{
	char **p = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(p);
}

/**
 * reallocMem - realloc
 * @ptr: pointer
 * @sizeOld: size of old
 * @sizeNew: size of new
 *
 * Return: pointer
 */
void *reallocMem(void *ptr, unsigned int sizeOld, unsigned int sizeNew)
{
	char *p;

	if (!ptr)
		return (malloc(sizeNew));
	if (!sizeNew)
		return (free(ptr), NULL);
	if (sizeNew == sizeOld)
		return (ptr);

	p = malloc(sizeNew);
	if (!p)
		return (NULL);

	sizeOld = sizeOld < sizeNew ? sizeOld : sizeNew;
	while (sizeOld--)
		p[sizeOld] = ((char *)ptr)[sizeOld];
	free(ptr);
	return (p);
}
