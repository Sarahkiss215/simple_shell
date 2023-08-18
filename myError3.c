#include "shell.h"

/**
 * check_esyntax - Checkks for a syntax error
 * @info: relevant information
 * @input: input string
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int check_esyntax(list_sh *info, char *input)
{
	int start = 0;
	int char1 = 0;
	int index = 0;

	char1 = first_char(input, &start);
	if (char1 == -1)
	{
		print_esyntax(info, input, start, 0);
		return (1);
	}
	index = op_error(input + start, 0, *(input + start));
	if (index != 0)
	{
		print_esyntax(info, input, start + index, 1);
		return (1);
	}
	return (0);
}

/**
 * print_esyntax - prints when a syntax error is found
 * @info: data structure
 * @input: input string
 * @index: index of the error
 * @bool: to control msg error
 *
 * Return: Nothing.
 */
void print_esyntax(list_sh *info, char *input, int index, int bool)
{
	char *msg1, *msg2, *msg3, *error, *counter;
	int len;

	if (input[index] == ';')
	{
		if (bool == 0)
			msg1 = (input[index + 1] == ';' ? ";;" : ";");
		else
			msg1 = (input[index - 1] == ';' ? ";;" : ";");
	}
	if (input[index] == '|')
		msg1 = (input[index + 1] == '|' ? "||" : "|");

	if (input[index] == '&')
		msg1 = (input[index + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(info->counter);
	len = _strlen(info->av[0]) + _strlen(counter);
	len += _strlen(msg1) + _strlen(msg2) + _strlen(msg3) + 2;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg1);
	_strcat(error, msg3);
	_strcat(error, "\0");
	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * first_char - finds index of the first char
 * @input: input string
 * @index: index of the string
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int first_char(char *input, int *index)
{

	for (*index = 0; input[*index]; *index += 1)
	{
		if (input[*index] == ' ' || input[*index] == '\t')
		{
			continue;
		}
		if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
		{
			return (-1);
		}
		break;
	}
	return (0);
}

/**
 * op_error - finds syntax errors
 * @input: input string
 * @index: index
 * @last: last char read
 *
 * Return: index of error, 0 otherwise.
 */
int op_error(char *input, int index, char last)
{
	int counter = 0;

	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (op_error(input + 1, index + 1, last));
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (index);
	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (index);

		if (last == '|')
		{
			counter = char_repeated(input, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (index);
		if (last == '&')
		{
			counter = char_repeated(input, 0);
			if (counter == 0 || counter > 1)
				return (index);
		}
	}
	return (op_error(input + 1, index + 1, *input));
}

/**
 * char_repeated - counts the repetitions of a char
 * @input: input string
 * @index: index of the string
 * Return: Number of times repeated.
 */
int char_repeated(char *input, int index)
{
	if (*(input - 1) == *input)
	{
		return (char_repeated(input - 1, index + 1));
	}
	return (index);
}
