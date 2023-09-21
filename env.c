#include "shell.h"

/**
 * print_environment - Print the current environment.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int print_environment(info_t *info)
{
    printListStr(info->env);
    return (0);
}

/**
 * get_environment_variable - Get the value of an environment variable.
 * @info: Pointer to the shell's information structure.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = string_starts_with(node->str, name);
        if (value && *value)
            return (value);
        node = node->next;
    }
    return (NULL);
}

/**
 * set_environment_variable - Set or update an environment variable.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Usage: setenv <name> <value>\n");
        return (1);
    }

    if (set_environment_variable(info))
        return (0);

    return (1);
}

/**
 * unset_environment_variable - Remove an environment variable.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Usage: unsetenv <name> [<name> ...]\n");
        return (1);
    }

    for (i = 1; i <= info->argc; i++)
        unset_environment_variable(info);

    return (0);
}

/**
 * initialize_environment_list - Initialize the environment linked list.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int initialize_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    info->env = node;
    return (0);
}
