#include "shell.h"

/**
 * @brief Check if the current character in the buffer is a command chaining delimiter.
 *
 * This function checks if the current character in the buffer, along with the next character,
 * forms a command chaining delimiter (e.g., "||" or "&&").
 *
 * @param info Pointer to the parameter struct.
 * @param buf  The character buffer.
 * @param p    Pointer to the current position in the buffer.
 * @return     1 if a command chaining delimiter is found, 0 otherwise.
 */
int is_command_chaining(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* Found the end of this command */
    {
        buf[j] = 0; /* Replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return (0);
    }
    *p = j;
    return (1);
}

/**
 * @brief Check whether command chaining should continue based on the last command's status.
 *
 * This function determines whether command chaining (AND or OR) should continue based on
 * the last command's exit status.
 *
 * @param info Pointer to the parameter struct.
 * @param buf  The character buffer.
 * @param p    Pointer to the current position in the buffer.
 * @param i    Starting position in the buffer.
 * @param len  Length of the buffer.
 */
void check_command_chaining(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * @brief Replace aliases in the tokenized string.
 *
 * This function attempts to replace aliases in the tokenized string with their corresponding values.
 *
 * @param info Pointer to the parameter struct.
 * @return     1 if an alias is replaced, 0 otherwise.
 */
int replace_aliases(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = findNodeWithPrefix(info->alias, info->argv[0], '=');
        if (!node)
        {
            return (0);
        }
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
        {
            return (0);
        }
        p =strdup(p + 1);
        if (!p)
        {
            return (0);
        }
        info->argv[0] = p;
    }
    return (1);
}

/**
 * @brief Replace variables in the tokenized string.
 *
 * This function replaces variables in the tokenized string with their corresponding values.
 *
 * @param info Pointer to the parameter struct.
 * @return     Always returns 0.
 */
int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            continue;
        }

        if (!strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]), strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]), strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = findNodeWithPrefix(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]), strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], strdup(""));
    }
    return (0);
}

/**
 * @brief Replace a string with a new one.
 *
 * This function replaces a string with a new one, freeing the memory allocated for the old string.
 *
 * @param old Pointer to the old string.
 * @param new The new string.
 * @return    Always returns 1.
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
