#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	/* Create a new node and set its values */
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		/* If the list is empty, make the new node the head */
		*head = new;
	}
	else
	{
		/* Find the last node in the list */
		while (temp->next != NULL)
			temp = temp->next;

		/* Append the new node to the end of the list */
		temp->next = new;
	}

	return (*head);
}


/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_sep_list(sep_list **head)
{
	if (head != NULL && *head != NULL)
	{
		sep_list *current = *head;
		sep_list *next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		*head = NULL;
	}
}


/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */

line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;

	if (*head == NULL)
	{
		/* If the list is empty, the new node becomes the head */
		*head = new;
	}
	else
	{
		/* Traverse the list to find the last node */
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;

		/* Add the new node as the next node of the last node */
		temp->next = new;
	}

	return (*head);
}


/**
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_line_list(line_list **head)
{
	if (head != NULL && *head != NULL)
	{
		line_list *current = *head;
		line_list *next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		*head = NULL;
	}
}
