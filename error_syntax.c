#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}


/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */

int error_sep_op(char *input, int i, char last)
{
	int count = 0;

	/* If the end of the input string is reached, return 0 (no errors) */
	if (*input == '\0')
		return (0);

	/* Skip whitespaces and continue checking the next character */
	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	/* If the current character is a semicolon (';') */
	if (*input == ';')
	{
		/* Check if the last character was '|', '&', or ';' */
		if (last == '|' || last == '&' || last == ';')
			return (i); /* Return the index 'i' as an error */
	}
	/* If the current character is a pipe ('|') */
	else if (*input == '|')
	{
		/* Check if the last character was ';', '&', or '|' */
		if (last == ';' || last == '&')
			return (i); /* Return the index 'i' as an error */

		/* If the last character was '|', check for consecutive occurrences */
		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i); /* Return the index 'i' as an error */
		}
	}
	/* If the current character is an ampersand ('&') */
	else if (*input == '&')
	{
		/* Check if the last character was ';', '|', or '&' */
		if (last == ';' || last == '|')
			return (i); /* Return the index 'i' as an error */

		/* If the last character was '&', check for consecutive occurrences */
		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i); /* Return the index 'i' as an error */
		}
	}

	/* Continue checking the next character and increment 'i' */
	return (error_sep_op(input + 1, i + 1, *input));
}



/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */

int first_char(char *input, int *i)
{
	*i = 0; /* Initialize the index to 0 */

	while (input[*i] != '\0')
	{
		if (input[*i] == ' ' || input[*i] == '\t')
		{
			(*i)++; /* Skip whitespaces and continue checking the next character */
		}
		else if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
		{
			return (-1); /* Return -1 to indicate an error if any of the separators is found */
		}
		else
		{
			break; /* Break the loop when a valid character is found */
		}
	}

	return (0); /* Return 0 if a valid character is found (no error) */
}


/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */

void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg = NULL;
	char *error, *counter;
	int msg_len, program_name_len;
	const char *error_template = ": Syntax error: \"%c\" unexpected\n";
	int length;

	if (input[i] == ';' && (bool == 0 || input[i - 1] == ';'))
	{
		msg = (input[i + 1] == ';' ? ";;" : ";");
	}
	else if (input[i] == '|' && input[i + 1] == '|')
	{
		msg = "||";
	}
	else if (input[i] == '&' && input[i + 1] == '&')
	{
		msg = "&&";
	}

	if (msg != NULL)
	{
		counter = aux_itoa(datash->counter);
		program_name_len = _strlen(datash->av[0]);
		msg_len = _strlen(msg);
		length = program_name_len + _strlen(counter) + msg_len + _strlen(error_template) + 1;

		error = malloc(length);
		if (error != NULL)
		{
			snprintf(error, length, "%s: %s: Syntax error: \"%s\" unexpected\n", datash->av[0], counter, msg);
			write(STDERR_FILENO, error, length - 1);
			free(error);
		}
		free(counter);
	}
}


/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */

int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = first_char(input, &begin);
	int i = 0;
	int count;
	char last;

	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	/* New logic to check for syntax error */
	last = *(input + begin);
	while (input[begin + i] != '\0')
	{
		if (input[begin + i] == ';' || input[begin + i] == '|' || input[begin + i] == '&')
		{
			if (input[begin + i] == last)
			{
				count = repeated_char(input + begin + i, 0);
				if (count == 0 || count > 1)
				{
					print_syntax_error(datash, input, begin + i, 1);
					return (1);
				}
			}
			last = input[begin + i];
		}
		i++;
	}

	return (0);
}
