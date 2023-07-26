#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */

void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX], *dir, *cp_pwd, *cp_strtok_pwd, *token, *lastToken = NULL;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];

	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}

	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = _strdup(cp_pwd);
	token = _strtok(cp_strtok_pwd, "/");
	while (token != NULL)
	{
		lastToken = token;
		token = _strtok(NULL, "/");
	}

	if (lastToken != NULL)
	{
		chdir(lastToken);
		set_env("PWD", lastToken, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
	free(cp_strtok_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));
	dir = datash->args[1];

	cp_pwd = _strdup(pwd);
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		free(cp_pwd);
		return;
	}

	cp_dir = _strdup(dir);
	set_env("OLDPWD", cp_pwd, datash);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */

void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *cp_pwd, *cp_oldpwd, *p_oldpwd, newline;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);
	if (p_oldpwd == NULL)
	{
		cp_oldpwd = _strdup(cp_pwd);
	}
	else
	{
		cp_oldpwd = _strdup(p_oldpwd);
	}

	if (chdir(cp_oldpwd) == -1)
	{
		perror("cd");
		free(cp_pwd);
		free(cp_oldpwd);
		datash->status = 1;
		return;
	}

	set_env("OLDPWD", cp_pwd, datash);
	set_env("PWD", cp_oldpwd, datash);

	newline = '\n';
	write(STDOUT_FILENO, cp_oldpwd, _strlen(cp_oldpwd));
	write(STDOUT_FILENO, &newline, 1);

	free(cp_pwd);
	free(cp_oldpwd);
	datash->status = 0;
}


/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */

void cd_to_home(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *home;

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL || chdir(home) == -1)
	{
		if (home != NULL)
			get_error(datash, 2);
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		datash->status = 1;
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);

	free(p_pwd);
	datash->status = 0;
}
