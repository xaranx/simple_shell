#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag = NULL;

	/* Concatenate the error message parts */
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);

	/* Check if the second argument starts with '-' */
	if (datash->args[1][0] == '-')
	{
		/* Allocate memory for the illegal flag, e.g., "-x" */
		illegal_flag = malloc(3);
		if (illegal_flag != NULL)
		{
			illegal_flag[0] = '-';
			illegal_flag[1] = datash->args[1][1];
			illegal_flag[2] = '\0';

			/* Concatenate the illegal flag to the error message */
			_strcat(error, illegal_flag);

			free(illegal_flag); /* Free the memory used for the illegal flag */
		}
	}
	else
	{
		/* Concatenate the second argument to the error message */
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n"); /* Append a newline character */
	_strcat(error, "\0"); /* Null-terminate the error message */

	return (error); /* Return the error message */
}



/**
 * error_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */

char *error_get_cd(data_shell *datash)
{
	char *error, *msg;
	int length, len_id;

	char *ver_str = aux_itoa(datash->counter);

	/* Determine the appropriate error message based on the second argument */
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	/* Calculate the total length required for the error message */
	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;

	/* Allocate memory for the error message */
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	/* Construct the error message using the new logic */
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, msg);
	_strcat(error, datash->args[1]);

	free(ver_str);

	return (error);
}



/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */

char *error_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}



/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
