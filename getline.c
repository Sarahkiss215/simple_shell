#include "shell.h"

/**
 * print_str - prints the input string.
 * @_eof: return value of getline function
 *
 * Return: input string
 */
char *print_str(int *_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*_eof = getline(&input, &bufsize, stdin);
	return (input);
}

/**
 * ass_line - assigns the line var for get_line function
 * @ptr: Buffer that store string
 * @str: string that is been called to line
 * @n: size of line(bytes)
 * @j: size of buffer
 *
 * Return: Nothing
 */
void ass_line(char **ptr, size_t *n, char *str, size_t j)
{

	if (*ptr == NULL)
	{
		if  (j > BUF_SIZE)
			*n = j;
		else
			*n = BUF_SIZE;
		*ptr = str;
	}
	else if (*n < j)
	{
		if (j > BUF_SIZE)
			*n = j;
		else
			*n = BUF_SIZE;
		*ptr = str;
	}
	else
	{
		_strcpy(*ptr, str);
		free(str);
	}
}

/**
 * get_line - gets string from input from stream
 * @ptr: buffer that stores the string
 * @n: size of ptr
 * @stream: stream to read from
 *
 * Return: number of bytes
 */
ssize_t get_line(char **ptr, size_t *n, FILE *stream)
{
	int line;
	static ssize_t str;
	ssize_t strline;
	char *buffer;
	char i = 'z';

	str = 0;
	if (str == 0)
		fflush(stream);
	else
		return (-1);
	buffer = malloc(sizeof(char) * BUF_SIZE);
	if (buffer == 0)
		return (-1);
	while (i != '\n')
	{
		line = read(STDIN_FILENO, &i, 1);
		if (line == -1 || (line == 0 && str == 0))
		{
			free(buffer);
			return (-1);
		}
		if (line == 0 && str != 0)
		{
			str++;
			break;
		}
		if (str >= BUF_SIZE)
			buffer = _realloc(buffer, str, str + 1);
		buffer[str] = i;
		str++;
	}
	buffer[str] = '\0';
	ass_line(ptr, n, buffer, str);
	strline = str;
	if (line != 0)
		str = 0;
	return (strline);
}
