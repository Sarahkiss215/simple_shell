#include "shell.h"

/**
 * strcat_error - function that concatenates the message for cd error
 * @info: relevant information(directory)
 * @msg: message to print
 * @error: output message
 * @str: counter lines
 *
 * Return: error message
 */
char *strcat_error(list_sh *info, char *msg, char *error, char *str)
{
	char *flag;

	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, msg);
	if (info->args[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = info->args[1][1];
		flag[2] = '\0';
		_strcat(error, flag);
		free(flag);
	}
	else
	{
		_strcat(error, info->args[1]);
	}
	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * *exit_sh_error - generic error message for exit in get_exit
 * @info: relevant information (counter, arguments)
 *
 * Return: Error message
 */
char *exit_sh_error(list_sh *info)
{
	int len;
	char *error;
	char *str;

	str = aux_itoa(info->counter);
	len = _strlen(info->av[0]) + _strlen(str);
	len += _strlen(info->args[0]) + _strlen(info->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, info->args[1]);
	_strcat(error, "\n\0");
	free(str);
	return (error);
}

/**
 * *no_error - generic error message for command not found
 * @info: relevant information (counter, arguments)
 *
 * Return: Error message
 */
char *no_error(list_sh *info)
{
	int len;
	char *error;
	char *str;

	str = aux_itoa(info->counter);
	len = _strlen(info->av[0]) + _strlen(str);
	len += _strlen(info->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(str);
	return (error);
}

/**
 * *cd_error - error message for cd command
 * @info: relevant information (directory)
 *
 * Return: Error message
 */
char *cd_error(list_sh *info)
{
	int len1, len2;
	char *error, *str, *msg;

	str = aux_itoa(info->counter);
	if (info->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len2 = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len2 = _strlen(info->args[1]);
	}
	len1 = _strlen(info->av[0]) + _strlen(info->args[0]);
	len1 += _strlen(str) + _strlen(msg) + len2 + 5;
	error = malloc(sizeof(char) * (len1 + 1));
	if (error == 0)
	{
		free(str);
		return (NULL);
	}
	error = strcat_error(info, msg, error, str);
	free(str);
	return (error);
}
