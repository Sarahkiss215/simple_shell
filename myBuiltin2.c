#include "shell.h"

/**
 * info_helpbuiltin - Help information for the builtin help.
 *
 * Return: Nothing
 */
void info_helpbuiltin(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * info_cdbuiltin - Help information for the builtin cd command.
 *
 * Return: Nothing.
 */
void info_cdbuiltin(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * info_alias - Help information for the builtin alias.
 *
 * Return: Nothing.
 */
void info_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * get_builtin - builtin that passes the command in the arg
 * @cmd: command
 *
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(list_sh *)
{
	builtin_t builtin[] = {
		{ "env", print_env },
		{ "exit", exit_sh },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_current },
		{ "help", print_help },
		{ NULL, NULL }
	};
	int index = 0;

	for (; builtin[index].name; index++)
	{
		if (_strcmp(builtin[index].name, cmd) == 0)
		{
			break;
		}
	}
	return (builtin[index].f);
}

/**
 * print_help - retrieves help messages
 * @info: relevant information (args and input)
 *
 * Return: Return 0
 */
int print_help(list_sh *info)
{
	if (info->args[1] == 0)
		entry_info_env();
	else if (_strcmp(info->args[1], "setenv") == 0)
		set_envbuiltin();
	else if (_strcmp(info->args[1], "env") == 0)
		info_envbuiltin();
	else if (_strcmp(info->args[1], "unsetenv") == 0)
		unset_envbuiltin();
	else if (_strcmp(info->args[1], "help") == 0)
		info_helpbuiltin();
	else if (_strcmp(info->args[1], "exit") == 0)
		info_exitbuiltin();
	else if (_strcmp(info->args[1], "cd") == 0)
		info_cdbuiltin();
	else if (_strcmp(info->args[1], "alias") == 0)
		info_alias();
	else
		write(STDERR_FILENO, info->args[0],
				_strlen(info->args[0]));
	info->status = 0;
	return (1);
}
