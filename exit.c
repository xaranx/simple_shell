#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */

int exit_shell(data_shell *datash)
{
	if (datash->args[1] != NULL)
	{
		/* Convert the argument to an unsigned integer using strtol */
		char *endptr;
		unsigned long ustatus = strtoul(datash->args[1], &endptr, 10);

		/* Check for valid conversion and the absence of extra characters */
		if (*endptr != '\0' || (ustatus == ULONG_MAX && errno == ERANGE))
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}

		/* Check if the value is within the range of a signed integer */
		if (ustatus > INT_MAX)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}

		datash->status = (int)(ustatus % 256);
	}

	return (0);
}
