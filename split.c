#include "main.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */


char *swap_char(char *input, int bool)
{
	int i;
	char swap_char1, swap_char2, target_char;

	if (bool == 0)
	{
		swap_char1 = '|';
		swap_char2 = '&';
		target_char = '#';
	}
	else
	{
		swap_char1 = '#';
		swap_char2 = '#';
		target_char = '|';
	}

	for (i = 0; input[i]; i++)
	{
		if (input[i] == swap_char1)
		{
			if (input[i + 1] != swap_char1)
				input[i] = target_char;
			else
				i++;
		}

		if (input[i] == swap_char2)
		{
			if (input[i + 1] != swap_char2)
				input[i] = target_char;
			else
				i++;
		}
	}

	/* Swap back to the original characters if bool is not 0 */
	if (bool != 0)
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == target_char) ? swap_char1 : input[i];
		}
	}

	return (input);
}



/**
 * add_nodes - Adds separator and command lines to the respective lists.
 *
 * @head_s: Pointer to the head of the separator list.
 * @head_l: Pointer to the head of the command lines list.
 * @input: Input string to process.
 */

void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	/* Step 1: Convert characters '|' and '&' to non-printed characters */
	input = swap_char(input, 0);

	/* Step 2: Process the input string character by character */
	for (i = 0; input[i]; i++)
	{
		/* Step 3: If a semicolon is found, add a sep node to sep list */
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		/* 4: If '|' or '&' is found, add sep node to sep list & skip next char */
		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	/* Step 5: Tokenize modified input using ';' and '|' or '&' as delimiters */
	line = _strtok(input, ";|&");

	/* Step 6: Process each token (line) */
	do {
		/* Step 7: Swap chars '|' and '&' back to original values in the line */
		line = swap_char(line, 1);

		/* Step 8: Add the line node to the line list */
		add_line_node_end(head_l, line);

		/* Step 9: Get the next token (line) */
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}




/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */

void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep = 1;
	sep_list *ls_s = *list_s;
	line_list *ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		/* Determine if current sep should break loop based on datash->status */
		if (datash->status == 0 && (ls_s->separator == '&' || ls_s->separator == ';'))
		{
			loop_sep = 0;
		}
		else if (datash->status != 0 && (ls_s->separator == '|' || ls_s->separator == ';'))
		{
			loop_sep = 0;
		}
		else if (ls_s->separator == '|')
		{
			/* Move to the next line_list node for '|' separator */
			ls_l = ls_l->next;
			ls_s = ls_s->next;
		}
		else if (ls_s->separator == '&')
		{
			/* Move to the next line_list node for '&' separator */
			ls_l = ls_l->next;
			ls_s = ls_s->next;
		}

		/* Move to the next separator if we have not exited the loop */
		if (ls_s != NULL && !loop_sep)
		{
			ls_s = ls_s->next;
		}
	}

	*list_s = ls_s;
	*list_l = ls_l;
}


/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */

int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s = NULL;
	line_list *list_l;
	line_list *head_l = NULL;
	int loop = 1;

	/* Step 1: Add nodes for separators and command lines */
	add_nodes(&head_s, &head_l, input);

	list_l = head_l;

	while (list_l != NULL)
	{
		/* Step 2: Execute the current line */
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		/* Step 3: If the execution status is 0 (exit), break the loop */
		if (loop == 0)
			break;

		/* Step 4: Move to the next line and separator (if applicable) */
		go_next(&head_s, &list_l, datash);

		/* Step 5: Move to the next line */
		if (list_l != NULL)
			list_l = list_l->next;
	}

	/* Step 6: Free mem allocated for the separator and command line lists */
	free_sep_list(&head_s);
	free_line_list(&head_l);

	/* Step 7: Return 0 if the execution status was 0 (exit), else return 1 */
	return ((loop == 0) ? 0 : 1);
}


/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */

/* Split the input string into tokens based on the delimiter TOK_DELIM */
char **split_line(char *input)
{
	char *token;
	size_t bsize = 8; /* Initial buffer size */
	size_t i = 0;
	char **tokens = malloc(sizeof(char *) * bsize);

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);

	/* Loop until there are no more tokens */
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		/* Increase buffer size if needed */
		if (i >= bsize)
		{
			bsize += 8;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}

		token = _strtok(NULL, TOK_DELIM);
	}

	return (tokens);
}
