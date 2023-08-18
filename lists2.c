#include "shell.h"

/**
 * *add_var_end - adds a variable at the end of list_var.
 * @head: head of the linked list.
 * @var_len: length of the variable.
 * @val: value of the variable.
 * @val_len: length of the value.
 *
 * Return: address of the head.
 */
list_var *add_var_end(list_var **head, int var_len, char *val, int val_len)
{
	list_var *newvar, *temp;

	newvar = malloc(sizeof(list_var));
	if (newvar == NULL)
	{
		return (NULL);
	}
	newvar->var_len = var_len;
	newvar->val = val;
	newvar->val_len = val_len;
	newvar->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = newvar;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newvar;
	}
	return (*head);
}

/**
 * free_list_var - frees list_var list
 * @head: head of the linked list.
 *
 * Return: Nothing.
 */
void free_list_var(list_var **head)
{
	list_var *temp;
	list_var *newnode;

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
