#include "main.h"

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */


/* Shell Loop Function */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1; /* Set the loop control variable to 1 to start the loop */
	while (loop == 1) /* Execute the loop while the loop control variable is 1 */
	{
		/* Print the shell prompt */
		write(STDIN_FILENO, "--> ", 4);

		/* Read the input line, and check for end-of-file (i_eof) condition */
		input = read_line(&i_eof);

		if (i_eof != -1) /* If it's not an end-of-file condition */
		{
			/* Remove comments from the input */
			input = without_comment(input);
			if (input == NULL)
				continue; /* Skip to the next iteration if the input is empty */

			/* Check for syntax errors in the input */
			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2; /* Set the status to 2 for syntax error */
				free(input); /* Free the allocated memory for input */
				continue; /* Skip to the next iteration of the loop */
			}
			/* Replace variables in the input */
			input = rep_var(input, datash);
			/* Split and execute commands from the input */
			loop = split_commands(datash, input);

			datash->counter += 1; /* Increment the command counter */
			free(input); /* Free the allocated memory for input */
		}
		else
		{
			loop = 0; /* Set loop control variable to 0 to exit loop */
			free(input); /* Free allocated memory for input */
		}
	}
}

