#include "shell.h"

/**
 * _strtoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer if successful, -1 on error.
 */
int _strtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Print an error message to the standard error.
 * @info: Pointer to the information struct.
 * @error_msg: String containing the error message.
 *
 * Return: None.
 */
void print_error(info_t *info, char *error_msg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_integer(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_msg);
}

/**
 * print_integer - Print an integer to the specified file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_integer(int input, int fd)
{
	int (*print_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		print_char = _eputchar;

	if (input < 0)
	{
		absolute_value = -input;
		print_char('-');
		count++;
	}
	else
		absolute_value = input;

	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Convert a number to a string in the specified base.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Flags indicating conversion options.
 *
 * Return: A string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *character_set;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	character_set = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = character_set[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Replace the first '#' with '\0' in a string.
 * @buf: The string to modify.
 *
 * Return: None.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
