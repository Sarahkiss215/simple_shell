#include "shell.h"

/**
 * **get_token - tokenizes the input string
 * @input: input string.
 *
 * Return: string splitted.
 */
char **get_token(char *input)
{
	size_t size;
	size_t index;
	char **tokenptr;
	char *token;

	size = TOKEN_BUF_SIZE;
	tokenptr = malloc(sizeof(char *) * (size));
	if (tokenptr == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOKEN_DELIM);
	tokenptr[0] = token;
	for (index = 1; token != NULL; index++)
	{
		if (index == size)
		{
			size += TOKEN_BUF_SIZE;
			tokenptr = realloc_dptr(tokenptr, index, sizeof(char *) * size);
			if (tokenptr == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIM);
		tokenptr[index] = token;
	}
	return (tokenptr);
}

/**
 * add_nodes - add nodes in the lists
 * @head_op: head of operator list
 * @head_ln: head of command lines list
 * @input: input string
 *
 * Return: Nothing.
 */
void add_nodes(list_op **head_op, list_ln **head_ln, char *input)
{
	int index;
	char *line;

	input = _swapchar(input, 0);
	for (index = 0; input[index]; index++)
	{
		if (input[index] == ';')
			add_op_end(head_op, input[index]);

		if (input[index] == '|' || input[index] == '&')
		{
			add_op_end(head_op, input[index]);
			index++;
		}
	}
	line = _strtok(input, ";|&");
	do {
		line = _swapchar(line, 1);
		add_line_end(head_ln, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * *_swapchar - swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 *
 * Return: swapped string
 */
char *_swapchar(char *input, int bool)
{
	int index;

	if (bool == 0)
	{
		for (index = 0; input[index]; index++)
		{
			if (input[index] == '|')
			{
				if (input[index + 1] != '|')
					input[index] = 16;
				else
					index++;
			}
			if (input[index] == '&')
			{
				if (input[index + 1] != '&')
					input[index] = 12;
				else
					index++;
			}
		}
	}
	else
	{
		for (index = 0; input[index]; index++)
		{
			input[index] = (input[index] == 16 ? '|' : input[index]);
			input[index] = (input[index] == 12 ? '&' : input[index]);
		}
	}
	return (input);
}

/**
 * go_to_next - go to the next command line stored
 * @list_p: operator list
 * @list_l: command line list
 * @info: Relevant information.
 *
 * Return: Nothing.
 */
void go_to_next(list_op **list_p, list_ln **list_l, list_sh *info)
{
	int loop_op;
	list_op *ls_p;
	list_ln *ls_l;

	loop_op = 1;
	ls_p = *list_p;
	ls_l = *list_l;
	while (ls_p != NULL && loop_op)
	{
		if (info->status == 0)
		{
			if (ls_p->oper == '&' || ls_p->oper == ';')
				loop_op = 0;
			if (ls_p->oper == '|')
				ls_l = ls_l->next, ls_p = ls_p->next;
		}
		else
		{
			if (ls_p->oper == '|' || ls_p->oper == ';')
				loop_op = 0;
			if (ls_p->oper == '&')
				ls_l = ls_l->next, ls_p = ls_p->next;
		}
		if (ls_p != NULL && !loop_op)
			ls_p = ls_p->next;
	}
	*list_p = ls_p;
	*list_l = ls_l;
}

/**
 * _splitcmd - splits command lines
 * @info: relevant information
 * @input: input string
 *
 * Return: 0 to exit, 1 to continue
 */
int _splitcmd(list_sh *info, char *input)
{
	list_op *head_op, *list_p;
	list_ln *head_ln, *list_l;
	int loop;

	head_op = NULL;
	head_ln = NULL;
	add_nodes(&head_op, &head_ln, input);
	list_p = head_op;
	list_l = head_ln;
	while (list_l != NULL)
	{
		info->input = list_l->line;
		info->args = get_token(info->input);
		loop = line_exec(info);
		free(info->args);
		if (loop == 0)
			break;
		go_to_next(&list_p, &list_l, info);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	free_list_op(&head_op);
	free_list_ln(&head_ln);
	if (loop == 0)
		return (0);
	return (1);
}
