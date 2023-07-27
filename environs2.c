#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */

char *copy_info(char *name, char *value)
{
	int len_name = _strlen(name);
	int len_value = _strlen(value);

	char *new = (char *)malloc(sizeof(char) * (len_name + len_value + 2));

	if (new == NULL)
	{
		/* Handle memory allocation failure */
		return (NULL);
	}

	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */

void set_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_env, *name_env, *new_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(name, value);
			putenv(datash->_environ[i]); /* Update the environment variable */
			free(var_env);
			return;
		}
		free(var_env);
	}

	/* Create a new environment variable and add it to the _environ array */
	new_env = copy_info(name, value);
	if (new_env == NULL)
	{
		/* Handle memory allocation failure */
		return;
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = new_env;
	datash->_environ[i + 1] = NULL;
	putenv(datash->_environ[i]); /* Add the new environment variable */
}


/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */

int _setenv(data_shell *datash)
{
	int len_name, len_value, len_env;
	char *env_str;

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	/* Combine name and value into a single string in the format "name=value" */
	len_name = _strlen(datash->args[1]);
	len_value = _strlen(datash->args[2]);
	len_env = len_name + len_value + 2;
	env_str = malloc(sizeof(char) * len_env);
	if (env_str == NULL)
	{
		/* Handle memory allocation failure */
		return (1);
	}

	_strcpy(env_str, datash->args[1]);
	_strcat(env_str, "=");
	_strcat(env_str, datash->args[2]);

	/* Set the environment variable using putenv */
	if (putenv(env_str) != 0)
	{
		/* Handle error setting environment variable */
		get_error(datash, -1);
		free(env_str);
		return (1);
	}

	return (1);
}


/*
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */

int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	/* Find the index of the environment variable to unset */
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		if (_strcmp(datash->_environ[i], datash->args[1]) == 0)
		{
			k = i;
			break;
		}
	}
	/* If the variable is not found, return with an error */
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	/* Allocate memory for the new environment array without the unset variable */
	realloc_environ = malloc(sizeof(char *) * (i));
	/* Copy environment variables to the new array, skipping the unset variable */
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = _strdup(datash->_environ[i]);
			j++;
		}
	}
	realloc_environ[j] = NULL;
	/* Free memory for the old environment array a& update it with the new one */
	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}
	free(datash->_environ);
	datash->_environ = realloc_environ;

	return (1);
}
