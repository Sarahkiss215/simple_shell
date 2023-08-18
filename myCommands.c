#include "shell.h"

/**
 * command_exec - executes command lines
 * @info: relevant information (args and input)
 *
 * Return: 1 on success.
 */
int command_exec(list_sh *info)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = _isexecutable(info);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = loc_cmd(info->args[0], info->_environ);
		if (check_ecmd(dir, info) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = loc_cmd(info->args[0], info->_environ);
		else
			dir = info->args[0];
		execve(dir + exec, info->args, info->_environ);
	}
	else if (pd < 0)
	{
		perror(info->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	info->status = state / 256;
	return (1);
}

/**
 * check_ecmd - verifies if user has permissions to access
 * @dir: destination directory
 * @info: relevant information.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int check_ecmd(char *dir, list_sh *info)
{
	if (dir == NULL)
	{
		get_error(info, 127);
		return (1);
	}

	if (_strcmp(info->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(info, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(info->args[0], X_OK) == -1)
		{
			get_error(info, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * *loc_cmd - locates a command
 * @cmd: command name
 * @_environ: environment variable
 *
 * Return: location of the command.
 */
char *loc_cmd(char *cmd, char **_environ)
{
	char *path, *ptrpath, *tokenpath, *dir;
	int len1, len2, index;
	struct stat st;

	path = get_env("PATH", _environ);
	if (path)
	{
		ptrpath = _strdup(path);
		len2 = _strlen(cmd);
		tokenpath = _strtok(ptrpath, ":");
		index = 0;
		while (tokenpath != NULL)
		{
			if (_iscdir(path, &index))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len1 = _strlen(tokenpath);
			dir = malloc(len1 + len2 + 2);
			_strcpy(dir, tokenpath);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptrpath);
				return (dir);
			}
			free(dir);
			tokenpath = _strtok(NULL, ":");
		}
		free(ptrpath);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * _isexecutable - determines if is an executable
 * @info: relevant information.
 *
 * Return: 0 if is not an executable, other number if it does
 */
int _isexecutable(list_sh *info)
{
	struct stat st;
	int index;
	char *input;

	input = info->args[0];
	for (index = 0; input[index]; index++)
	{
		if (input[index] == '.')
		{
			if (input[index + 1] == '.')
				return (0);
			if (input[index + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[index] == '/' && index != 0)
		{
			if (input[index + 1] == '.')
				continue;
			index++;
			break;
		}
		else
			break;
	}
	if (index == 0)
		return (0);
	if (stat(input + index, &st) == 0)
	{
		return (index);
	}
	get_error(info, 127);
	return (-1);
}

/**
 * _iscdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @index: type int pointer of index.
 *
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int _iscdir(char *path, int *index)
{
	if (path[*index] == ':')
	{
		return (1);
	}
	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}
	if (path[*index])
		*index += 1;
	return (0);
}
