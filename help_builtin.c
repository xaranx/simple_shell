#include "main.h"

/**
 * aux_help - Help information for the builtin help.
 * Return: no return
 */

void aux_help(void)
{
	char *help_buffer;
	unsigned long int i;

	/* Define individual help messages */
	const char *help_messages[] = {
		"help: help [-dms] [pattern ...]\n",
		"\tDisplay information about builtin commands.\n ",
		"\tDisplays brief summaries of builtin commands.\n"
	};
	/* Calculate the total length of the help messages */
	size_t total_length = 0;

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		total_length += _strlen(help_messages[i]);
	}

	/* Create a buffer to store the combined help message */
	help_buffer = malloc(total_length + 1); /* +1 for null terminator */

	if (help_buffer == NULL)
	{
		/*
		 * Memory allocation failed; handle the error as needed
		 * For example, you can print an error message and exit the program.
		 * For simplicity, we just return without printing the help message.
		 */
		return;
	}
	/* Combine the help messages into the help_buffer */
	help_buffer[0] = '\0'; /* Initialize the buffer as an empty string */

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		_strcat(help_buffer, help_messages[i]);
	}
	/* Write the combined help message to the standard output */
	write(STDOUT_FILENO, help_buffer, total_length);
	/* Free the allocated memory */
	free(help_buffer);
}


/**
 * aux_help_alias - Help information for the builtin alias.
 * Return: no return
 */

void aux_help_alias(void)
{
	char *help_buffer;
	unsigned long int i;

	/* Define individual help messages */
	const char *help_messages[] = {
		"alias: alias [- p] [name[=value]...]\n",
		"\tDefine or display aliases.\n "
	};

	/* Calculate the total length of the help messages */
	size_t total_length = 0;

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		total_length += _strlen(help_messages[i]);
	}

	/* Create a buffer to store the combined help message */
	help_buffer = malloc(total_length + 1); /* +1 for null terminator */

	if (help_buffer == NULL)
	{
		/*
		 * Memory allocation failed; handle the error as needed
		 * For example, you can print an error message and exit the program.
		 * For simplicity, we just return without printing the help message.
		 */
		return;
	}
	/* Combine the help messages into the help_buffer */
	help_buffer[0] = '\0'; /* Initialize the buffer as an empty string */

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		_strcat(help_buffer, help_messages[i]);
	}
	/* Write the combined help message to the standard output */
	write(STDOUT_FILENO, help_buffer, total_length);
	/* Free the allocated memory */
	free(help_buffer);
}


/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */

void aux_help_cd(void)
{
	char *help_buffer;
	unsigned long int i;

	/* Define individual help messages */
	const char *help_messages[] = {
		"cd: cd [-L|[-P [-e]] [-@]] [dir]\n",
		"\tChange the shell working directory.\n "
	};

	/* Calculate the total length of the help messages */
	size_t total_length = 0;

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		total_length += _strlen(help_messages[i]);
	}
	/* Create a buffer to store the combined help message */
	help_buffer = malloc(total_length + 1); /* +1 for null terminator */

	if (help_buffer == NULL)
	{
		/*
		 * Memory allocation failed; handle the error as needed
		 * For example, you can print an error message and exit the program.
		 * For simplicity, we just return without printing the help message.
		 */
		return;
	}
	/* Combine the help messages into the help_buffer */
	help_buffer[0] = '\0'; /* Initialize the buffer as an empty string */

	for (i = 0; i < sizeof(help_messages) / sizeof(help_messages[0]); i++)
	{
		_strcat(help_buffer, help_messages[i]);
	}
	/* Write the combined help message to the standard output */
	write(STDOUT_FILENO, help_buffer, total_length);
	/* Free the allocated memory */
	free(help_buffer);
}


/**
 * get_help - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
 */
int get_help(data_shell *datash)
{

	if (datash->args[1] == 0)
		aux_help_general();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
				_strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
