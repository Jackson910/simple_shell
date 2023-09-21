#include "shell.h"

/**
 * @brief The main shell loop.
 *
 * @param info A pointer to the parameter and return info struct.
 * @param av The argument vector from main().
 * @return Returns 0 on success, 1 on error, or an error code.
 */
int main_shell_loop(info_t *info, char **av)
{
    ssize_t read_result = 0;
    int builtin_return_code = 0;

    while (read_result != -1 && builtin_return_code != -2)
    {
        initializeInfo(info);
        if (check_interactive_mode(info))
            _print_string("$ ");
        _eputchar(BUF_FLUSH);
        read_result = get_input(info);
        if (read_result != -1)
        {
            setInfo(info, av);
            builtin_return_code = find_and_execute_builtin(info);
            if (builtin_return_code == -1)
                find_and_execute_command(info);
        }
        else if (check_interactive_mode(info))
            _putchar('\n');
        freeInfo(info, 0);
    }
    writeHistory(info);
    freeInfo(info, 1);
    if (!check_interactive_mode(info) && info->status)
        exit(info->status);
    if (builtin_return_code == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_return_code);
}

/**
 * @brief Find and execute a built-in shell command.
 *
 * @param info A pointer to the parameter and return info struct.
 * @return Returns -1 if built-in not found,
 *         0 if built-in executed successfully,
 *         1 if built-in found but not successful,
 *         2 if built-in signals shell exit().
 */
int find_and_execute_builtin(info_t *info)
{

    int i, shell_builtin_return_code = -1;
    builtin_table builtintbl[] = {
        {"exit", exit_shell},
        {"env", print_environment},
        {"help", show_help},
        {"history", print_history},
        {"cd", change_directory},
        {"alias", manage_alias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
    {
        if (string_compare(info->argv[0], builtintbl[i].type))
        {
            info->line_count++;
            shell_builtin_return_code = builtintbl[i].func(info);
            break;
        }
    }
    return (shell_builtin_return_code);
}

/**
 * @brief Find and execute a shell command in the PATH.
 *
 * @param info A pointer to the parameter and return info struct.
 */
void find_and_execute_command(info_t *info)
{
    char *path = NULL;
    int i, shell_argument_count;

    info->path = info->argv[0];

    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, shell_argument_count = 0; info->arg[i]; i++)
	    if (!is_delimiter(info->arg[i], "\t\n"))
		    shell_argument_count++;
    if (!shell_argument_count)
        return;

    path = find_command_path(info, get_environment_variable(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_and_execute_command(info);
    }
    else
    {
        if ((check_interactive_mode(info) || get_environment_variable(info, "PATH=") || info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
            fork_and_execute_command(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * @brief Fork and execute a shell command.
 *
 * @param info A pointer to the parameter and return info struct.
 */
void fork_and_execute_command(info_t *info)
{
    pid_t shell_child_pid;

    shell_child_pid = fork();
    if (shell_child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (shell_child_pid == 0)
    {
        if (execve(info->path, info->argv, getEnvironment(info)) == -1)
        {
            freeInfo(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
