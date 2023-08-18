#include "shell.h"

/**
 * get_error - calls the error according the builtin,
 * @info: relevant information on  arguments
 * @err_val: error value
 *
 * Return: error
 */
int get_error(list_sh *info, int err_val)
{
	char *error;

	switch (err_val)
	{
		case -1:
			error = env_error(info
			break;
		case 126:
			error = path_126_error(info);
			break;
		case 127:
			error = no_error(info);
			break;
		case 2:
			if (_strcmp("exit", info->args[0]) == 0)
				error = exit_sh_error(info);
			else if (_strcmp("cd", info->args[0]) == 0)
				error = cd_error(info);
			break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	info->status = err_val;
	return (err_val);
}

/**
 * *env_error - error message for env in get_env.
 * @info: relevant information(counter, arguments)
 *
 * Return: error message.
 */
char *env_error(list_sh *info)
{
	int len;
	char *error;
	char *str;
	char *msg;

	str = aux_itoa(info->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(info->av[0]) + _strlen(str);
	len += _strlen(info->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(str);

	return (error);
}

/**
 * *path_126_error - error message for path and failure denied permission.
 * @info: relevant information(counter, arguments).
 *
 * Return: The error string.
 */
char *path_126_error(list_sh *info)
{
	int len;
	char *str;
	char *error;

	str = aux_itoa(info->counter);
	len = _strlen(info->av[0]) + _strlen(str);
	len += _strlen(info->args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(str);
	return (error);
}
