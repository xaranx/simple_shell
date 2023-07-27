#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */


void free_data(data_shell *datash)
{
	unsigned int i = 0;

	/* Free each element in the _environ array */
	while (datash->_environ[i] != NULL)
	{
		free(datash->_environ[i]);
		i++;
	}

	/* Free the _environ array itself */
	free(datash->_environ);

	/* Free the pid array */
	free(datash->pid);
}



/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */


void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	/* Find the number of elements in the 'environ' array */
	for (i = 0; environ[i]; i++)
		;

	/* Allocate memory for '_environ' array and copy the environment strings */
	datash->_environ = (char **)malloc(sizeof(char *) * (i + 1));
	if (datash->_environ != NULL)
	{
		for (i = 0; environ[i]; i++)
			datash->_environ[i] = _strdup(environ[i]);
		datash->_environ[i] = NULL;
	}

	/* Get the process ID and store it as a string */
	datash->pid = aux_itoa(getpid());
}



/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac; /* Silence unused parameter warning for ac */

	/* Set up signal handler for SIGINT */
	signal(SIGINT, get_sigint);

	/* Initialize the data_shell structure with environment and arguments */
	set_data(&datash, av);

	/* Start the shell loop */
	shell_loop(&datash);

	/* Free allocated memory and resources */
	free_data(&datash);

	/* If the shell was terminated due to SIGINT return 255 in that case */
	if (datash.status < 0)
		return (255);

	/* Return the status value from datash as the exit code */
	return (datash.status);
}

