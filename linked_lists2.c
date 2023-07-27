#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */

r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new;
	r_var **temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;

	/* Allocate memory for 'val' field and copy content of 'val' parameter */
	new->val = malloc((lval + 1) * sizeof(char));
	if (new->val == NULL)
	{
		free(new);
		return (NULL);
	}
	strncpy(new->val, val, lval);
	new->val[lval] = '\0'; /* Null-terminate the 'val' field */

	new->len_val = lval;
	new->next = NULL;

	/* Use double pointer to traverse the list and add new node at the end */
	temp = head;
	while (*temp != NULL)
		temp = &((*temp)->next);
	*temp = new;

	return (*head);
}



/**
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_rvar_list(r_var **head)
{
	r_var *current = *head;
	r_var *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;

		/* Free the 'val' field */
		free(temp->val);

		/* Free the current node */
		free(temp);
	}

	/* After freeing all nodes, set head to NULL */
	*head = NULL;
}
