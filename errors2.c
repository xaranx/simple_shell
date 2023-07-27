#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */

char *error_env(data_shell *datash)
{
	char *error = NULL;
	char *ver_str = aux_itoa(datash->counter);
	char *msg = ": Unable to add/remove from environment\n";

	/* Calculate the required length for the error message */
	int length = _strlen(datash->av[0]) + _strlen(ver_str) + _strlen(datash->args[0]) + _strlen(msg) + 4;

	/* Allocate memory for the error message */
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	/* Construct the error message using _strcpy and _strcat */
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");

	free(ver_str);

	return (error);
}


/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */

char *error_path_126(data_shell *datash)
{
	char *error = NULL;
	char *ver_str = aux_itoa(datash->counter);
	char *msg = ": Permission denied\n";

	/* Calculate the required length for the error message */
	int length = _strlen(datash->av[0]) + _strlen(ver_str) + _strlen(datash->args[0]) + _strlen(msg) + 4;

	/* Allocate memory for the error message */
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	/* Construct the error message using _strcpy and _strcat */
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");

	free(ver_str);

	return (error);
}



/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */

int get_error(data_shell *datash, int eval)
{
	char *error = NULL;

	if (eval == -1)
	{
		error = error_env(datash);
	}
	else if (eval == 126)
	{
		error = error_path_126(datash);
	}
	else if (eval == 127)
	{
		error = error_not_found(datash);
	}
	else if (eval == 2)
	{
		if (_strcmp("exit", datash->args[0]) == 0)
		{
			error = error_exit_shell(datash);
		}
		else if (_strcmp("cd", datash->args[0]) == 0)
		{
			error = error_get_cd(datash);
		}
	}

	if (error != NULL)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
