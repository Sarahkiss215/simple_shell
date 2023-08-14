#include "shell.h"

/**
 * _revString - reverses a string.
 * @s: string to be reversed.
 *
 * Return: Nothing.
 */
void _revString(char *s)
{
	int index = 0, n, length;
	char *string, temp;

	for (; index >= 0; index++)
	{
		if (s[index] == '\0')
			break;
	}
	string = s;
	for (n = 0; n < (index - 1); n++)
	{
		for (length = n + 1; length > 0; length--)
		{
			temp = *(string + length);
			*(string + length) = *(string + (length - 1));
			*(string + (length - 1)) = temp;
		}
	}
}

/**
 * _strdup - duplicates a string
 * @s: string to be duplicated
 *
 * Return: duplicated string
 */
char *_strdup(const char *s)
{
	char *newstring;
	size_t index;

	index = _strlen(s);
	newstring = malloc(sizeof(char) * (index + 1));
	if (newstring == NULL)
	{
		return (NULL);
	}
	_memcpy(newstring, s, index + 1);
	return (newstring);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: string to be treated
 *
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int length = 0;

	while (s[length] != 0)
	{
		length++;
	}
	return (length);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: string to be treated
 * @delim: delimiter.
 *
 * Return: string splitted.
 */
char *_strtok(char str[], const char *delim)
{
	static char *newstring, *str_end;
	char *str_start;
	unsigned int index, bool;

	if (str != NULL)
	{
		if (comp_char(str, delim))
			return (NULL);
		newstring = str;
		index = _strlen(str);
		str_end = &str[index];
	}
	str_start = newstring;
	if (str_start == str_end)
		return (NULL);
	for (bool = 0; *newstring; newstring++)
	{
		if (newstring != str_start)
			if (*newstring && *(newstring - 1) == '\0')
				break;
		for (index = 0; delim[index]; index++)
		{
			if (*newstring == delim[index])
			{
				*newstring = '\0';
				if (newstring == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *newstring)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}
