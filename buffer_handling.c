#include "shell.h"

/**
 * inputBuffer - chose getline or _getline
 * @info: struct std_infos
 * @buffer: address of buffer
 * @l: pointer of length var
 *
 * Return: bytes read
 */
ssize_t inputBuffer(std_infos *info, char **buffer, size_t *l)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*l)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_coms(*buffer);
			*l = r;
			info->cmd_buf = buffer;
		}
	}
	return (r);
}

/**
 * getInput - removes '\n' from getline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(std_infos *info)
{
	static char *b;
	static size_t i, j, l;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFLUSH);
	r = inputBuffer(info, &b, &l);
	if (r == -1)
		return (-1);
	if (l)
	{
		j = i;
		p = b + i;

		checkCMD(info, b, &j, i, l);
		while (j < l)
		{
			if (setChain(info, b, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = b;
	return (r);
}

/**
 * readBuffer - reads a buffer
 * @info: struct std_infos
 * @b: buffer
 * @i: size of the buffer
 *
 * Return: buffer
 */
ssize_t readBuffer(std_infos *info, char *b, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, b, BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line from STDIN
 * @info: struct std_infos
 * @ptr: address of pointer to buffer
 * @length: size of preallocated buffer
 *
 * Return: s
 */
int _getline(std_infos *info, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readBuffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strsrch(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocMem(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_putstr("\n");
	_putstr("$ ");
	_putchar(BUFFLUSH);
}
