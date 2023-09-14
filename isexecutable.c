#include "shell.h"

/**
 * is_executable - Checks if a file is an executable command.
 * @info: Pointer to the info_t structure (not used).
 * @path: Path to the file being checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_executable(info_t *info, char *path)
{
    struct stat st;

    (void)info;

    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }

    return 0;
}

/**
 * extract_substring - Extracts a substring from a string.
 * @source: The source string.
 * @start: The starting index.
 * @end: The ending index.
 *
 * Return: A pointer to a new buffer containing the extracted substring.
 */
char *extract_substring(char *source, int start, int end)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < end; i++)
    {
        if (source[i] != ':')
        {
            buffer[k++] = source[i];
        }
    }

    buffer[k] = '\0';

    return buffer;
}

/**
 * find_command_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info_t structure (not used).
 * @pathstr: The PATH string containing directories.
 * @cmd: The command to find.
 *
 * Return: A pointer to the full path of the command if found, or NULL if not found.
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;

    if ((strlen(cmd) > 2) && string_starts_with(cmd, "./"))
    {
        if (is_executable(info, cmd))
        {
            return cmd;
        }
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = extract_substring(pathstr, curr_pos, i);

            if (!*path)
            {
                string_concatenate(path, cmd);
            }
            else
            {
                string_concatenate(path, "/");
                string_concatenate(path, cmd);
            }

            if (is_executable(info, path))
            {
                return path;
            }

            if (!pathstr[i])
            {
                break;
            }

            curr_pos = i;
        }

        i++;
    }

    return NULL;
}
