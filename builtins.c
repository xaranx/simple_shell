#include "main.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash) = NULL;

	if (datash->args[0] != NULL)
	{
		builtin = get_builtin(datash->args[0]);
	}

	if (builtin)
	{
		return (builtin(datash));
	}
	else
	{
		return (cmd_exec(datash));
	}
}

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	static builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shell},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_shell},
		{"help", get_help},
		{NULL, NULL}};
	int i = 0;

	while (builtin[i].name != NULL && _strcmp(builtin[i].name, cmd) != 0)
	{
		i++;
	}

	return (builtin[i].f);
}
