#include "shell.h"

/**
 * comp_env - compares the names of environment variables
 * @env_name: name of the environment variable to be compared to
 * @name: the name of environment variable passed
 *
 * Return: 0 if are not equal,the value otherwise.
 */
int comp_env(const char *env_name, const char *name)
{
	int index = 0;

	for (; env_name[index] != '='; index++)
	{
		if (env_name[index] != name[index])
			return (0);
	}
	return (index + 1);
}

/**
 * *get_env - gets the environment variable
 * @name: name of the environment variable
 * @_environ: the environment variable
 *
 * Return: value of environment variable if found, NULL otherwise.
 */
char *get_env(const char *name, char **_environ)
{
	char *env = NULL;
	int index = 0, mvmnt = 0;

	for (; _environ[index]; index++)
	{
		mvmnt = comp_env(_environ[index], name);
		if (mvmnt)
		{
			env = _environ[index];
			break;
		}
	}
	return (env + mvmnt);
}

/**
 * print_env - prints the evironment variables
 *@info: relevant information
 * Return: 1 on success.
 */
int print_env(list_sh *info)
{
	int n = 0, m = 0;

	for (; info->_environ[n]; n++)
	{
		for (m = 0; info->_environ[n][m]; m++)
			;
		write(STDOUT_FILENO, info->_environ[n], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	info->status = 0;
	return (1);
}

/**
 * _setenv - sets the names of environment variables
 *@info: relevant information
 * Return: 1 on success, 0 otherwise
 */
int _setenv(list_sh *info)
{

	if (info->args[1] == NULL || info->args[2] == NULL)
	{
		get_error(info, -1);
		return (1);
	}

	setEnv(info->args[1], info->args[2], info);

	return (1);
}

/**
 * setEnv - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @info: relevant information (environ)
 *
 * Return: Nothing.
 */
void setEnv(char *name, char *value, list_sh *info)
{
	int index = 0;
	char *environ_var, *environ_name;

	for (; info->_environ[index]; index++)
	{
		environ_var = _strdup(info->_environ[index]);
		environ_name = _strtok(environ_var, "=");
		if (_strcmp(environ_name, name) == 0)
		{
			free(info->_environ[index]);
			info->_environ[index] = _copyinfo(environ_name, value);
			free(environ_var);
			return;
		}
		free(environ_var);
	}
	info->_environ = _reallocdp(info->_environ,
			index, sizeof(char *) * (index + 2));
	info->_environ[index] = _copyinfo(name, value);
	info->_environ[index + 1] = NULL;
}
