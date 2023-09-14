#include "shell.h"

/**
 * @brief Calculate the length of a string.
 *
 * This function calculates and returns the length of the given string 's'.
 *
 * @param s The string whose length to calculate.
 * @return The length of the string 's'.
 */
int string_length(char *s)
{
	int length = 0;

	if (!s)
		return 0;

	while (*s++)
		length++;

	return length;
}

/**
 * @brief Compare two strings lexicographically.
 *
 * This function compares two strings 's1' and 's2' lexicographically.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return Returns a negative value if 's1' < 's2', a positive value if 's1' > 's2',
 *         and 0 if 's1' == 's2'.
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return 0;
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * @brief Check if one string starts with another.
 *
 * This function checks if the string 'haystack' starts with the substring 'needle'.
 *
 * @param haystack The string to search.
 * @param needle The substring to find.
 * @return Returns the address of the next character in 'haystack' after 'needle' if found,
 *         or NULL if 'needle' is not found at the beginning of 'haystack'.
 */
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return NULL;
	return (char *)haystack;
}

/**
 * @brief Concatenate two strings.
 *
 * This function concatenates (appends) the contents of the 'src' string to the end of the 'dest' string.
 *
 * @param dest The destination buffer.
 * @param src The source buffer.
 * @return A pointer to the destination buffer.
 */
char *string_concatenate(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return result;
}
