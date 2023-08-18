#include "shell.h"

/**
 * _loopsh - Loop of shell
 * @info: relevant information (av, input, args)
 *
 * Return: Nothing.
 */
void _loopsh(list_sh *info)
{
	int loop = 1, i_eof;
	char *str;

	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 3);
		str = print_str(&i_eof);
		if (i_eof != -1)
		{
			str = no_comment(str);
			if (str == NULL)
				continue;
			if (check_esyntax(info, str) == 1)
			{
				info->status = 2;
				free(str);
				continue;
			}
			str = replace_var(str, info);
			loop = sep_cmd(info, str);
			info->counter += 1;
			free(str);
		}
		else
		{
			loop = 0;
			free(str);
		}
	}
}

/**
 * del_comment - deletes comments from the input
 * @str: input string
 *
 * Return: input with no comments.
 */
char *del_comment(char *str)
{
	int index = 0, till = 0;

	for (; str[index]; index++)
	{
		if (str[index] == '#')
		{
			if (index == 0)
			{
				free(str);
				return (NULL);
			}
			if (str[index - 1] == ' ' || str[index - 1] == '\t' ||
					str[index - 1] == ';')
				till = index;
		}
	}
	if (till != 0)
	{
		str = _realloc(str, index, till + 1);
		str[till] = '\0';
	}
	return (str);
}
