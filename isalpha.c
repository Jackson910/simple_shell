#include "shell.h"

/**
 * check_interactive_mode - Check if the shell is in interactive mode.
 * @info: Pointer to the shell's information structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int check_interactive_mode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, char *delim)
{
    while (*delim) {
        if (*delim == c)
            return 1;
        delim++;
    }
    return 0;
}

/**
 * is_alphabetic - Check if a character is an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_alphabetic(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_integer - Convert a string to an integer.
 * @s: The string to convert.
 *
 * Return: The converted integer or 0 if no valid number is found.
 */
int string_to_integer(char *s)
{
    int i = 0;
    int sign = 1;
    int flag = 0;
    unsigned int result = 0;

    while (s[i] != '\0' && flag != 2) {
        if (s[i] == '-')
            sign *= -1;
        else if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
        i++;
    }

    return (sign == -1) ? -result : result;
}
