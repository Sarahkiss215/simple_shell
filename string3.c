#include "shell.h"

/**
 * comp_char - compare characters of strings
 * @str: string to be treated
 * @delim: delimiter.
 *
 * Return: 1 if are same, 0 otherwise.
 */
int comp_char(char str[], const char *delim)
{
	unsigned int index1;
	unsigned int index2, m;

	for (index1 = 0, m = 0; str[index1]; index1++)
	{
		for (index2 = 0; delim[index2]; index2++)
		{
			if (str[index1] == delim[index2])
			{
				m++;
				break;
			}
		}
	}
	if (index1 == m)
		return (1);
	return (0);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int index = 0;

	for (; s[index]; index++)
	{
		if (s[index] < 48 || s[index] > 57)
			return (0);
	}
	return (1);
}
