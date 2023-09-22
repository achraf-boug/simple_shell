#include "shell.h"

/**
 * setChain - set command chaining
 * @in: Pointer to info struct.
 * @buffer: buffer
 * @ad: Pointer to the index of chaining symbol
 *
 * Return: 1 if OK, 0 KO.
 */

int setChain(std_infos *in, char *buffer, size_t *ad)
{
	size_t j = *ad;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		in->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		in->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ad = j;
	return (1);
}

/**
 * checkCMD - adjust buffer based on chaining type
 * @in: Pointer to info struct.
 * @buffer: buffer
 * @pst: position tracker within the buffer
 * @i: Current position
 * @lg: Length of the buffer.
 *
 * Return: void
 */
void checkCMD(std_infos *in, char *buffer, size_t *pst, size_t i, size_t lg)
{
	size_t j = *pst;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			buffer[i] = 0;
			j = lg;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			buffer[i] = 0;
			j = lg;
		}
	}

	*pst = j;
}

/**
 * replaceAlias - Replace command name with alias argument
 * @in: Pointer to info struct.
 *
 * Return: 1 if OK, 0 if KO
 */
int replaceAlias(std_infos *in)
{
	int i;
	list_str *st;
	char *par;

	for (i = 0; i < 10; i++)
	{
		st = nodeStart(in->alias, in->argv[0], '=');
		if (!st)
			return (0);
		free(in->argv[0]);
		par = _strsrch(st->s, '=');
		if (!par)
			return (0);
		par = _strcpy2(par + 1);
		if (!par)
			return (0);
		in->argv[0] = par;
	}
	return (1);
}

/**
 * getParam - Return param values
 * @in: Pointer to info struct
 *
 * Return: 0
 */
int getParam(std_infos *in)
{
	int i = 0;
	list_str *str;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;

		if (!_strcmp(in->argv[i], "$?"))
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strTonum(in->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in->argv[i], "$$"))
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strTonum(getpid(), 10, 0)));
			continue;
		}
		str = nodeStart(in->env, &in->argv[i][1], '=');
		if (str)
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strsrch(str->s, '=') + 1));
			continue;
		}
		_strreplace(&in->argv[i], _strcpy2(""));

	}
	return (0);
}

/**
 * _strreplace - Replace old string with a new one
 * @strold: Pointer to the old string
 * @strnew: Pointer to the new string
 *
 * Return: 1
 */
int _strreplace(char **strold, char *strnew)
{
	free(*strold);
	*strold = strnew;
	return (1);
}
