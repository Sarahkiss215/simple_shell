#include "shell.h"

/**
 * *add_line_end - adds a command line at the end of a list_ln.
 * @head: head of the linked list.
 * @line: command line.
 *
 * Return: address of the head.
 */
list_ln *add_line_end(list_ln **head, char *line)
{
	list_ln *newline, *temp;

	newline = malloc(sizeof(list_ln));
	if (newline == NULL)
	{
		return (NULL);
	}
	newline->line = line;
	newline->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = newline;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newline;
	}
	return (*head);
}

/**
 * free_list_ln - frees list_ln
 * @head: head of the linked list.
 *
 * Return: Nothing.
 */
void free_list_ln(list_ln **head)
{
	list_ln *temp;
	list_ln *newnode;

	if (head != NULL)
	{
		newnode = *head;
		while ((temp = newnode) != NULL)
		{
			newnode = newnode->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * *add_op_end - adds an operator found at the end of list_op.
 * @head: head of the linked list.
 * @op: operator found (; | &).
 *
 * Return: address of the head.
 */
list_op *add_op_end(list_op **head, char op)
{
	list_op *newnode, *temp;

	newnode = malloc(sizeof(list_op));
	if (newnode == NULL)
	{
		return (NULL);
	}
	newnode->oper = op;
	newnode->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = newnode;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (*head);
}

/**
 * free_list_op - frees list_op list
 * @head: head of the linked list.
 *
 * Return: Nothing.
 */
void free_list_op(list_op **head)
{
	list_op *temp;
	list_op *newnode;

	if (head != NULL)
	{
		newnode = *head;
		while ((temp = newnode) != NULL)
		{
			newnode = newnode->next;
			free(temp);
		}
		*head = NULL;
	}
}
