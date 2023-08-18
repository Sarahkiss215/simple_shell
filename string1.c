#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: the destination of the copied string
 * @src: the source of string
 *
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	int index1 = 0;
	int index2 = 0;

	for (; dest[index1] != '\0'; index1++)
		;
	for (; src[index2] != '\0'; index2++)
	{
		dest[index1] = src[index2];
		index1++;
	}
	dest[index1] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings.
 * @s1: first string
 * @s2: second string
 *
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int index = 0;

	for (; s1[index] == s2[index] && s1[index]; index++)
		;
	if (s1[index] > s2[index])
	{
		return (1);
	}
	if (s1[index] < s2[index])
	{
		return (-1);
	}
	return (0);
}

/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 *
 * Return: number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int index1 = 0;
	int index2, n;

	for (; *(s + index1) != '\0'; index1++)
	{
		n = 1;
		for (index2 = 0; *(accept + index2) != '\0'; index2++)
		{
			if (*(s + index1) == *(accept + index2))
			{
				n = 0;
				break;
			}
		}
		if (n == 1)
			break;
	}
	return (index1);
}

/**
 * _strchr - locates a character in a string,
 * @s: string to be searched through
 * @c: character to be located
 *
 * Return: pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int index = 0;

	for (; *(s + index) != '\0'; index++)
		if (*(s + index) == c)
			return (s + index);
	if (*(s + index) == c)
		return (s + index);
	return ('\0');
}

/**
 * *_strcpy - Copies the string
 * @dest: the destination of the copied string
 * @src:  the source of string
 *
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	size_t index = 0;

	for (; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';
	return (dest);
}
