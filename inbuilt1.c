#include "shell.h"

/**
 * print_history - Display the command history, one command per line with line numbers.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int print_history(info_t *info)
{
    printList(info->history);
    return (0);
}

/**
 * unset_alias - Unset an alias by name.
 * @info: Pointer to the shell's information structure.
 * @alias_name: The name of the alias to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias_name)
{
    char *equals_pos, original_char;
    int result;

    equals_pos = _strchr(alias_name, '=');

    if (!equals_pos)
        return (1);

    original_char = *equals_pos;
    *equals_pos = '\0';

    result = deleteNodeAtIdex(&(info->alias),
                          getNodeIndex(info->alias, findNodeWithPrefix(info->alias, alias_name, -1)));

    *equals_pos = original_char;

    return (result);
}

/**
 * set_alias - Set or update an alias.
 * @info: Pointer to the shell's information structure.
 * @alias_str: The alias string in the format "name=value".
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias_str)
{
    char *equals_pos;

    equals_pos = _strchr(alias_str, '=');

    if (!equals_pos)
        return (1);

    if (!*++equals_pos)
        return (unset_alias(info, alias_str));

    unset_alias(info, alias_str);

    return (addNodeEnd(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - Print the name and value of an alias.
 * @alias_node: The alias node to print.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *alias_node)
{
    char *equals_pos = NULL, *alias_name = NULL;

    if (alias_node)
    {
        equals_pos = _strchr(alias_node->str, '=');

        for (alias_name = alias_node->str; alias_name <= equals_pos; alias_name++)
            _putchar(*alias_name);

        _putchar('\'');
        _print_string(equals_pos + 1);
        _print_string("'\n");

        return (0);
    }

    return (1);
}

/**
 * manage_alias - Manage shell aliases, including listing, setting, and unsetting.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
    int i;
    char *equals_pos = NULL;
    list_t *alias_node = NULL;

    if (info->argc == 1)
    {
        alias_node = info->alias;

        while (alias_node)
        {
            print_alias(alias_node);
            alias_node = alias_node->next;
        }

        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        equals_pos = _strchr(info->argv[i], '=');

        if (equals_pos)
            set_alias(info, info->argv[i]);
        else
            print_alias(findNodeWithPrefix(info->alias, info->argv[i], '='));
    }

    return (0);
}
