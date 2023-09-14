#include "shell.h"

/**
 * initializeInfo - Initializes fields in an info_t struct.
 * @info: Pointer to the info_t struct.
 */
void initializeInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * setInfo - Sets fields in an info_t struct based on command line arguments.
 * @info: Pointer to the info_t struct.
 * @av: Argument vector.
 */
void setInfo(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = split_string_with_delimiter(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_aliases(info);
        replace_variables(info);
    }
}

/**
 * freeInfo - Frees memory allocated for fields in an info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: True if freeing all fields.
 */
void freeInfo(info_t *info, int all)
{
    free(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            freeList(&(info->env));
        if (info->history)
            freeList(&(info->history));
        if (info->alias)
            freeList(&(info->alias));
        free(info->environ);
        info->environ = NULL;
        safeFree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}
