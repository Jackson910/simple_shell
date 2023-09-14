#include "shell.h"

/**
 * @brief Split a string into words using a delimiter string.
 *
 * This function splits the input string 'str' into words based on the delimiter string 'd'.
 *
 * @param str The input string to be split.
 * @param d   The delimiter string. If NULL, a space character is used as the default delimiter.
 * @return    A pointer to an array of strings, or NULL on failure.
 */
char **split_string_with_delimiter(char *str, char *d)
{
    int i, j, k, m, num_words = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!d)
        d = " ";

    for (i = 0; str[i] != '\0'; i++)
        if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
            num_words++;

    if (num_words == 0)
        return NULL;

    words = malloc((1 + num_words) * sizeof(char *));
    if (!words)
        return NULL;

    for (i = 0, j = 0; j < num_words; j++)
    {
        while (is_delimiter(str[i], d))
            i++;

        k = 0;
        while (!is_delimiter(str[i + k], d) && str[i + k])
            k++;

        words[j] = malloc((k + 1) * sizeof(char));
        if (!words[j])
        {
            for (k = 0; k < j; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (m = 0; m < k; m++)
            words[j][m] = str[i++];

        words[j][m] = '\0';
    }

    words[j] = NULL;
    return words;
}

/**
 * @brief Split a string into words using a single delimiter character.
 *
 * This function splits the input string 'str' into words based on the single delimiter character 'd'.
 *
 * @param str The input string to be split.
 * @param d   The delimiter character.
 * @return    A pointer to an array of strings, or NULL on failure.
 */
char **split_string_with_single_delimiter(char *str, char d)
{
    int i, j, k, m, num_words = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return NULL;

    for (i = 0; str[i] != '\0'; i++)
        if ((str[i] != d && str[i + 1] == d) ||
            (str[i] != d && !str[i + 1]) || str[i + 1] == d)
            num_words++;

    if (num_words == 0)
        return NULL;

    words = malloc((1 + num_words) * sizeof(char *));
    if (!words)
        return NULL;

    for (i = 0, j = 0; j < num_words; j++)
    {
        while (str[i] == d && str[i] != d)
            i++;

        k = 0;
        while (str[i + k] != d && str[i + k] && str[i + k] != d)
            k++;

        words[j] = malloc((k + 1) * sizeof(char));
        if (!words[j])
        {
            for (k = 0; k < j; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (m = 0; m < k; m++)
            words[j][m] = str[i++];

        words[j][m] = '\0';
    }

    words[j] = NULL;
    return words;
}
