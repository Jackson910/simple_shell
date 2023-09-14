#include "shell.h"

/**
 * _strncpy - Copy a string with a maximum length.
 * @dest: Destination string to copy to.
 * @src: Source string to copy from.
 * @n: Maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenate two strings with a maximum length.
 * @dest: First string to concatenate to.
 * @src: Second string to concatenate from.
 * @n: Maximum number of characters to concatenate.
 *
 * Return: A pointer to the concatenated string.
 */
char *string_concatenate(char *dest, char *src)
{
	int i, j, n;
	char *s = dest;

	i = 0;
	j = 0;
	n = 0;
	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locate a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
