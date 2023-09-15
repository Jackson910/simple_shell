#include "shell.h"

/**
 * input_buf - Buffers chained commands from standard input.
 * @info: Structure containing shell information.
 * @buf: Address of the buffer to store input.
 * @len: Address of the length variable.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			buildHistoryList(info, *buf, info->histcount++);
		}
	}

	return (r);
}

/**
 * get_input - Retrieves a line of input without the newline character.
 * @info: Structure containing shell information.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1) /* EOF */
		return (-1);

	if (len) /* There are commands left in the chain buffer */
	{
		j = i; /* Initialize new iterator to current buf position */
		p = buf + i; /* Get pointer for return */

		check_command_chaining(info, buf, &j, i, len);

		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_command_chaining(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'' */

		if (i >= len) /* Reached the end of the buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Not a chain; pass back buffer from _getline() */
	return (r); /* Return length of buffer from _getline() */
}

/**
 * read_buf - Reads data into a buffer.
 * @info: Structure containing shell information.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Structure containing shell information.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Total number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, k);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
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
 * sigintHandler - Blocks the Ctrl-C signal.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_print_string("\n");
	_print_string("$ ");
	_putchar(BUF_FLUSH);
}
