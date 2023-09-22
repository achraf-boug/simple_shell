#include "shell.h"

/**
 * getCmdPath - Check if a given path points to a regular file
 * @in: Pointer to the std_infos struct
 * @p: Path
 *
 * Return: 1 if OK, 0 KO
 */
int getCmdPath(std_infos *in, char *p)
{
	struct stat str;

	(void)in;
	if (!p || stat(p, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _strncpy2 - Create a duplicate substring
 * @str: string.
 * @start: start
 * @stop: end
 *
 * Return: Pointer to the duplicated substring.
 */
char *_strncpy2(char *str, int start, int stop)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * returnFullPath - return full path of a command
 * @in: Pointer to std_infos struct
 * @str: Colon-separated paths
 * @cd: Command name
 *
 * Return: Full path if found, else NULL
 */
char *returnFullPath(std_infos *in, char *str, char *cd)
{
	int i = 0, position = 0;
	char *ph;

	if (!str)
		return (NULL);
	if ((_strlen(cd) > 2) && _strstart(cd, "./"))
	{
		if (getCmdPath(in, cd))
			return (cd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			ph = _strncpy2(str, position, i);
			if (!*ph)
				_strcat(ph, cd);
			else
			{
				_strcat(ph, "/");
				_strcat(ph, cd);
			}
			if (getCmdPath(in, ph))
				return (ph);
			if (!str[i])
				break;
			position = i;
		}
		i++;
	}
	return (NULL);
}
