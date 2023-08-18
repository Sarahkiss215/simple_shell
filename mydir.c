#include "shell.h"

/**
 * cd_current - changes directory to current
 * @info: relevant information on directories
 *
 * Return: 1 on success, 0 otherwise.
 */
int cd_current(list_sh *info)
{
	char *dir;
	int homedir1, homedir2, dashdir;

	dir = info->args[1];
	if (dir != NULL)
	{
		homedir1 = _strcmp("$HOME", dir);
		homedir2 = _strcmp("~", dir);
		dashdir = _strcmp("--", dir);
	}
	if (dir == NULL || !homedir1 || !homedir2 || !dashdir)
	{
		cd_home(info);
		return (1);
	}
	if (_strcmp("-", dir) == 0)
	{
		cd_back(info);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(info);
		return (1);
	}
	cd_to(info);
	return (1);
}

/**
 * cd_home - changes to home directory
 * @info: relevant information on directories
 *
 * Return: Nothing.
 */
void cd_home(list_sh *info)
{
	char *pwdir, *homedir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pwdir = _strdup(pwd);
	homedir = get_env("HOME", info->_environ);
	if (homedir == NULL)
	{
		setEnv("OLDPWD", pwdir, info);
		free(pwdir);
		return;
	}
	if (chdir(homedir) == -1)
	{
		get_error(info, 2);
		free(pwdir);
		return;
	}

	_setEnv("OLDPWD", pwdir, info);
	_setEnv("PWD", homedir, info);
	free(pwdir);
	info->status = 0;
}

/**
 * cd_back - changes to the previous directory
 * @info: relevant information on directories
 *
 * Return: Nothing.
 */
void cd_back(list_sh *info)
{
	char pwd[PATH_MAX];
	char *pwdir, *oldpwd, *cp_pwdir, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwdir = _strdup(pwd);
	oldpwd = get_env("OLDPWD", info->_environ);
	if (oldpwd == NULL)
		cp_oldpwd = cp_pwdir;
	else
		cp_oldpwd = _strdup(oldpwd);

	_setEnv("OLDPWD", cp_pwdir, info);
	if (chdir(cp_oldpwd) == -1)
		_setEnv("PWD", cp_pwdir, info);
	else
		_setEnv("PWD", cp_oldpwd, info);

	pwdir = get_env("PWD", info->_environ);
	write(STDOUT_FILENO, pwdir, _strlen(pwdir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwdir);
	if (oldpwd)
		free(cp_oldpwd);
	info->status = 0;
	chdir(pwdir);
}

/**
 * cd_dot - changes to the parent directory
 * @info: relevant information on directories.
 *
 * Return: Nothing.
 */
void cd_dot(list_sh *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwdir1, *cp_pwdir2;

	getcwd(pwd, sizeof(pwd));
	cp_pwdir1 = _strdup(pwd);
	_setEnv("OLDPWD", cp_pwdir1, info);
	dir = info->args[1];
	if (_strcmp(".", dir) == 0)
	{
		_setEnv("PWD", cp_pwdir1, info);
		free(cp_pwdir1);
		return;
	}
	if (_strcmp("/", cp_pwdir1) == 0)
	{
		free(cp_pwdir1);
		return;
	}
	cp_pwdir2 = cp_pwdir1;
	_revString(cp_pwdir2);
	cp_pwdir2 = _strtok(cp_pwdir2, "/");
	if (cp_pwdir2 != NULL)
	{
		cp_pwdir2 = _strtok(NULL, "\0");
		if (cp_pwdir2 != NULL)
			_revString(cp_pwdir2);
	}
	if (cp_pwdir2 != NULL)
	{
		chdir(cp_pwdir2);
		_setEnv("PWD", cp_pwdir2, info);
	}
	else
	{
		chdir("/");
		_setEnv("PWD", "/", info);
	}
	info->status = 0;
	free(cp_pwdir1);
}

/**
 * cd_to - changes to a directory given by the user
 * @info: relevant information on directories
 *
 * Return: Nothing.
 */
void cd_to(list_sh *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwdir, *cpy_dir;

	getcwd(pwd, sizeof(pwd));
	dir = info->args[1];
	if (chdir(dir) == -1)
	{
		get_error(info, 2);
		return;
	}
	cp_pwdir = _strdup(pwd);
	_setEnv("OLDPWD", cp_pwdir, info);
	cpy_dir = _strdup(dir);
	_setEnv("PWD", cpy_dir, info);
	free(cp_pwdir);
	free(cpy_dir);
	info->status = 0;
	chdir(dir);
}
