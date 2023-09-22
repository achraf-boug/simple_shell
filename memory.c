#include "shell.h"

/**
 * flushMem - flush memory
 * @p: Pointer to be freed
 *
 * Return: 1 if OK, 0 if KO
 */
int flushMem(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
