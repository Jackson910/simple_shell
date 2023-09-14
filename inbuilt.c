#include "shell.h"

/**
 * exit_shell - Exit the shell with a specified exit status.
 * @info: Pointer to the shell's information structure.
 *
 * Return: 1 if there is an invalid exit status, -2 otherwise.
 */
int exit_shell(info_t *info)
{
    int exit_status;

    if (info->argv[1])
    {
        exit_status = string_to_integer(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            print_error(info, "Invalid exit status: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * change_directory - Change the current directory of the shell process.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int change_directory(info_t *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);

    if (!current_dir)
        _print_string("TODO: Handle getcwd failure here\n");

    if (!info->argv[1])
    {
        target_dir = _get_environment_variable(info, "HOME=");
        if (!target_dir)
            chdir_ret = chdir((target_dir = _get_environment_variable(info, "PWD=")) ? target_dir : "/");
        else
            chdir_ret = chdir(target_dir);
    }
    else if (string_compare(info->argv[1], "-") == 0)
    {
        if (!_get_environment_variable(info, "OLDPWD="))
        {
            _print_string(current_dir);
            _putchar('\n');
            return 1;
        }
        _print_string(_get_environment_variable(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((target_dir = _get_environment_variable(info, "OLDPWD=")) ? target_dir : "/");
    }
    else
    {
        target_dir = info->argv[1];
        chdir_ret = chdir(target_dir);
    }

    if (chdir_ret == -1)
    {
        print_error(info, "Unable to change directory to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        setEnvironmentVar(info, "OLDPWD", _get_environment_variable(info, "PWD="));
        setEnvironmentVar(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * show_help - Display help information for the shell.
 * @info: Pointer to the shell's information structure.
 *
 * Return: Always 0.
 */
int show_help(info_t *info)
{
    char **arguments = info->argv;

    _print_string("Help: Functionality not yet implemented.\n");

    if (arguments && *arguments)
    {
        _print_string(*arguments);
    }

    return 0;
}
