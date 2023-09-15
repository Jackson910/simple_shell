#include "shell.h"

/**
 * getEnvironment - Returns a copy of the environment variables as a string array.
 * @info: Structure containing relevant information.
 * Return: A string array containing environment variables.
 */
char **getEnvironment(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = listToStrings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * unsetEnvironmentVar - Removes an environment variable.
 * @info: Structure containing relevant information.
 * @var: The name of the environment variable to remove.
 * Return: 1 if the variable was successfully removed, 0 otherwise.
 */
int unsetEnvironmentVar(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = string_starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * setEnvironmentVar - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing relevant information.
 * @var: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * Return: Always returns 0.
 */
int setEnvironmentVar(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(strlen(var) + strlen(value) + 2);
    if (!buf)
        return (1);
    _strncpy(buf, var, 99);
    strncat(buf, "=", 99);
    strncat(buf, value, 99);
    node = info->env;
    while (node)
    {
        p = string_starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}
