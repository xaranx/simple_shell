#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;

	/* Loop through the environment variables */
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr] && in[j] == _envr[row][chr]; chr++, j++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}
		}
	}

	/* Loop until a space, tab, semicolon, or newline is encountered */
	for (j = 0; in[j] && in[j] != ' ' && in[j] != '\t' && in[j] != ';' && in[j] != '\n'; j++)
		;

	add_rvar_node(h, j, NULL, 0);
}



/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */

int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
			{
				add_rvar_node(h, 2, st, lst);
				i++;
			}
			else if (in[i + 1] == '$')
			{
				add_rvar_node(h, 2, data->pid, lpd);
				i++;
			}
			else if (in[i + 1] == '\n' || in[i + 1] == '\0' ||
					in[i + 1] == ' ' || in[i + 1] == '\t' || in[i + 1] == ';')
			{
				add_rvar_node(h, 0, NULL, 0);
			}
			else
			{
				check_env(h, in + i, data);
			}
		}
		i++;
	}

	return (i);
}



/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */


char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	i = j = 0;

	while (i < nlen)
	{
		if (input[j] == '$')
		{
			if (indx->len_var == 0 && indx->len_val == 0)
			{
				new_input[i++] = input[j++];
			}
			else if (indx->len_var > 0 && indx->len_val == 0)
			{
				j += indx->len_var;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i++] = indx->val[k];
				}
				j += indx->len_var;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i++] = input[j++];
		}
	}

	return (new_input);
}



/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */

char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;
	/* Get the current status as a string */
	status = aux_itoa(datash->status);
	head = NULL;
	/* Find the length of the input string after variable replacement */
	olen = check_vars(&head, input, status, datash);
	/* If no variables found, return the original input */
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	/* Compute the new length of the string after replacement */
	nlen = 0;
	indx = head;
	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}
	nlen += olen;
	/* Allocate memory for the new_input string */
	new_input = malloc(sizeof(char) * (nlen + 1));
	if (new_input == NULL)
	{
		/* Memory allocation error, clean up and return NULL */
		free(status);
		free_rvar_list(&head);
		return (NULL);
	}
	new_input[nlen] = '\0';
	/* Replace variables in the input string and store the result in new_input */
	new_input = replaced_input(&head, input, new_input, nlen);
	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
