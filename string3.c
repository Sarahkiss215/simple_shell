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

/**
 * _atoi - converts a string to an integer.
 * @s: string to be converted
 *
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int index = 0, size = 0;
	unsigned int res = 0, prod1 = 1, prod2 = 1, diff;

	while (*(s + index) != '\0')
	{
		if (size > 0 && (*(s + index) < '0' || *(s + index) > '9'))
			break;

		if (*(s + index) == '-')
			prod1 *= -1;

		if ((*(s + index) >= '0') && (*(s + index) <= '9'))
		{
			if (size > 0)
				prod2 *= 10;
			size++;
		}
		index++;
	}
	for (diff = index - size; diff < index; diff++)
	{
		res = res + ((*(s + diff) - 48) * prod2);
		prod2 /= 10;
	}
	return (res * prod1);
}

/**
 * aux_itoa - function converts int to string.
 * @n: number to be converted
 *
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int num;
	int length = _getlen(n);
	char *str;

	str = malloc(sizeof(char) * (length + 1));
	if (str == 0)
		return (NULL);
	*(str + length) = '\0';

	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
	{
		num = n;
	}
	length--;
	do {
		*(str + length) = (num % 10) + '0';
		num = num / 10;
		length--;
	}
	while (num > 0)
		;
	return (str);
}

/**
 * _getlen - gets the lenght of a number.
 * @n: number to be treated
 *
 * Return: Lenght of a number.
 */
int _getlen(int n)
{
	unsigned int num;
	int length;

	length = 1;
	if (n < 0)
	{
		length++;
		num = n * -1;
	}
	else
	{
		num = n;
	}
	while (num > 9)
	{
		length++;
		num = num / 10;
	}
	return (length);
}
