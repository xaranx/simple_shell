#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int i = 0;

	while (nenv[i] && nenv[i] != '=' && nenv[i] == name[i])
	{
		i++;
	}

	if (nenv[i] == '=' && name[i] == '\0')
	{
		return (i + 1);
	}

	return (0);
}


/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env = NULL;
	int i, j;

	for (i = 0; _environ[i] != NULL; i++)
	{
		j = 0;
		while (_environ[i][j] != '=' && _environ[i][j] == name[j])
		{
			j++;
		}

		if (_environ[i][j] == '=' && name[j] == '\0')
		{
			ptr_env = _environ[i] + j + 1;
			break;
		}
	}

	return (ptr_env);
}


/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */

int _env(data_shell *datash)
{
	int i = 0;
	int j;

	while (datash->_environ[i] != NULL)
	{
		j = 0;
		while (datash->_environ[i][j] != '\0')
			j++;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);

		i++;
	}

	datash->status = 0;
	return (1);
}
