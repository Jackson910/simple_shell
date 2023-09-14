#include "shell.h"

/**
 * @brief Copy a source string to a destination string.
 *
 * This function copies the contents of the source string 'src' to the destination
 * string 'dest'.
 *
 * @param dest The destination string.
 * @param src  The source string to be copied.
 * @return     A pointer to the destination string.
 */
char *_string_copy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/**
 * @brief Duplicate a string.
 *
 * This function creates a duplicate of the input string 'str' by allocating memory
 * for the new string and copying its contents.
 *
 * @param str The string to be duplicated.
 * @return    A pointer to the duplicated string.
 */
char *_string_duplicate(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 * @brief Print a string to stdout.
 *
 * This function prints the string 'str' to the standard output (stdout).
 *
 * @param str The string to be printed.
 */
void _print_string(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * @brief Write a character to stdout.
 *
 * This function writes the character 'c' to the standard output (stdout).
 *
 * @param c The character to be printed.
 * @return  On success, 1 is returned. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}
