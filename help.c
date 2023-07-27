#include "main.h"

/**
 * aux_help_env - Help information for the builtin env
 * Return: no return
 */

void aux_help_env(void)
{
	char *help1 = "env: env [option] [name=value] [command [args]]\n\t";
	char *help2 = "Print the environment of the shell.\n";
	char *help_buffer;

	/* Calculate the total length of both help messages */
	size_t total_length = _strlen(help1) + _strlen(help2);

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

	/* Copy both help messages to the help_buffer */
	_strcpy(help_buffer, help1);
	_strcat(help_buffer, help2);

	/* Write the combined help message to the standard output */
	write(STDOUT_FILENO, help_buffer, total_length);

	/* Free the allocated memory */
	free(help_buffer);
}


/**
 * aux_help_setenv - Help information for the builtin setenv
 * Return: no return
 */

void aux_help_setenv(void)
{
	unsigned long int i;
	char *help_buffer;
	const char *help_messages[] = {
		"setenv: setenv (const char *name, const char *value, int replace)\n\t",
		"Add a new definition to the environment\n"
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
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */

void aux_help_unsetenv(void)
{
	unsigned long int i;
	char *help_buffer;
	const char *help_messages[] = {
		"unsetenv: unsetenv (const char *name, const char *value, int replace)\n\t",
		"Remove an entry completely from the environment\n"
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
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */

void aux_help_general(void)
{
	unsigned long int i;
	char *help_buffer;
	const char *help_messages[] = {
		"--> Enoh Koldflames bash, version 1.0 (1)-release\n",
		"These shell commands are defined internally. Type 'help' to see the list.\n",
		"Type 'help name' to find out more about the function 'name'.\n\n",
		"alias: alias [name=['string']]\ncd: cd [-L|[-P [-e]] [-@]] [dir]\n",
		"exit: exit [n]\nenv: env [option] [name=value] [command [args]]\n",
		"setenv: setenv [variable] [value]\nunsetenv: unsetenv [variable]\n"
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
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */

void aux_help_exit(void)
{
	unsigned long int i;
	char *help_buffer;
	const char *help_messages[] = {
		"exit: exit [n]\n Exit shell.\n",
		"Exits the shell with a status of N. If N is omitted, the exit",
		"status is that of the last command executed\n"
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
