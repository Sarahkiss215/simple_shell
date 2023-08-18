#include "shell.h"

/**
 * *_copyinfo - copies info for creation of new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *_copyinfo(char *name, char *value)
{
	char *newname;
	int name_len, value_len, length;

	name_len = _strlen(name);
	value_len = _strlen(value);
	length = name_len + value_len + 2;

	newname = malloc(sizeof(char) * (length));
	_strcpy(newname, name);
	_strcat(newname, "=");
	_strcat(newname, value);
	_strcat(newname, "\0");

	return (newname);
}

/**
 * _unsetenv - deletes a environment variable
 * @info: information on env name
 *
 * Return: 1 on success.
 */
int _unsetenv(list_sh *info)
{
	char **new_env;
	char *env_var, *env_name;
	int index = 0, n, m;

	if (info->args[1] == NULL)
	{
		get_error(info, -1);
		return (1);
	}
	m = -1;
	for (; info->_environ[index]; index++)
	{
		env_var = _strdup(info->_environ[index]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, info->args[1]) == 0)
		{
			m = index;
		}
		free(env_var);
	}
	if (m == -1)
	{
		get_error(info, -1);
		return (1);
	}
	new_env = malloc(sizeof(char *) * (index));
	for (index = n = 0; info->_environ[index]; index++)
	{
		if (index != m)
		{
			new_env[n] = info->_environ[index];
			n++;
		}
	}
	new_env[n] = NULL;
	free(info->_environ[m]);
	free(info->_environ);
	info->_environ = new_env;
	return (1);
}
