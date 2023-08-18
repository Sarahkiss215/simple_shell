#include "shell.h"

/**
 * *replace_var - replaces string into vars
 * @input: input string
 * @info: data structure
 * Return: replaced string
 */
char *replace_var(char *input, list_sh *info)
{
	list_var *head, *index;
	char *status, *str;
	int len1, len2;

	status = aux_itoa(info->status);
	head = NULL;
	len1 = _checkvar(&head, input, status, info);
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	index = head;
	len2 = 0;
	while (index != NULL)
	{
		len2 += (index->val_len - index->var_len);
		index = index->next;
	}
	len2 += len1;
	str = malloc(sizeof(char) * (len2 + 1));
	str[len2] = '\0';
	str = rep_input(&head, input, str, len2);

	free(input);
	free(status);
	free_list_var(&head);

	return (str);
}

/**
 * rep_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @str: new input string (replaced)
 * @len: new length
 *
 * Return: replaced string
 */
char *rep_input(list_var **head, char *input, char *str, int len)
{
	list_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < len; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->var_len) && !(index->val_len))
			{
				str[i] = input[j];
				j++;
			}
			else if (index->var_len && !(index->val_len))
			{
				for (k = 0; k < index->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->val_len; k++)
				{
					str[i] = index->val[k];
					i++;
				}
				j += (index->var_len);
				i--;
			}
			index = index->next;
		}
		else
		{
			str[i] = input[j];
			j++;
		}
	}
	return (str);
}

/**
 * _checkvar - check if the typed variable is $$ or $?
 * @head: head of the linked list
 * @str: input string
 * @st: last status of the Shell
 * @data: data structure
 *
 * Return: index of variable.
 */
int _checkvar(list_var **head, char *str, char *st, list_sh *data)
{
	int index, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);
	for (index = 0; str[index]; index++)
	{
		if (str[index] == '$')
		{
			if (str[index + 1] == '?')
				add_var_end(head, 2, st, lst), index++;
			else if (str[index + 1] == '$')
				add_var_end(head, 2, data->pid, lpd), index++;
			else if (str[index + 1] == '\n')
				add_var_end(head, 0, NULL, 0);
			else if (str[index + 1] == '\0')
				add_var_end(head, 0, NULL, 0);
			else if (str[index + 1] == ' ')
				add_var_end(head, 0, NULL, 0);
			else if (str[index + 1] == '\t')
				add_var_end(head, 0, NULL, 0);
			else if (str[index + 1] == ';')
				add_var_end(head, 0, NULL, 0);
			else
				_checkenv(head, str + index, data);
		}
	}

	return (index);
}

/**
 * _checkenv - checks if the typed variable is an env variable
 * @head: head of linked list
 * @str: input string
 * @data: data structure
 *
 * Return: Nothing.
 */
void _checkenv(list_var **head, char *str, list_sh *data)
{
	int row, chr, index, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (index = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_var_end(head, index, _envr[row] + chr + 1, lval);
				return;
			}
			if (str[index] == _envr[row][chr])
				index++;
			else
				break;
		}
	}
	for (index = 0; str[index]; index++)
	{
		if (str[index] == ' ' || str[index] == '\t' ||
				str[index] == ';' || str[index] == '\n')
			break;
	}

	add_var_end(head, index, NULL, 0);
}
