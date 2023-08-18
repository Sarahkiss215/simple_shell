#include "shell.h"

/**
 * exit_sh - exits the shell
 * @info: relevant information(status and args)
 *
 * Return: 0 on success.
 */
int exit_sh(list_sh *info)
{
	unsigned int ustatus;
	int num1;
	int len;
	int num2;

	if (info->args[1] != NULL)
	{
		ustatus = _atoi(info->args[1]);
		num1 = _isdigit(info->args[1]);
		len = _strlen(info->args[1]);
		num2 = ustatus > (unsigned int)INT_MAX;
		if (!num1 || len > 10 || num2)
		{
			get_error(info, 2);
			info->status = 2;
			return (1);
		}
		info->status = (ustatus % 256);
	}
	return (0);
}

/**
 * line_exec - executes line commands.
 * @info: relevant information (args)
 *
 * Return: 1 on success, 0 otherwise.
 */
int line_exec(list_sh *info)
{
	int (*builtin)(list_sh *info);

	if (info->args[0] == NULL)
	{
		return (1);
	}
	builtin = get_builtin(info->args[0]);
	if (builtin != NULL)
	{
		return (builtin(info));
	}
	return (command_exec(info));
}

/**
 * get_sigint - Handle the crtl + c call
 * @sig: handles signal
 *
 * Return: Nothing.
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
