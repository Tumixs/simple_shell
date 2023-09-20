/*
 * Shell Builtins.
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
#include "builtin.h"
#include "env.h"
#include "path.h"

/**
 * runbuiltin - Executes a builtin routine.
 * @arg: Arguements to the routine.
 * Return: Returns the exit status of the command.
 */
int runbuiltin(char **arg)
{
	insider runner = NULL;
	int ret;

	runner = getbuiltin(arg[0]);
	if (runner == NULL)
		return (-1);
	ret = runner(arg);
	return (ret);
}
/**
 * getbuiltin - Gets a builtin function.
 * @cmd: Builtin identifier.
 *
 * Return: Returns the function poinetr, otherwise NULL if it exist's not.
 */
int (*getbuiltin(char *cmd))(char **cmd)
{
	builtin func[] = {
	    {"cd", cd},
	    {"setenv", setenv_msk},
	    {"unsetenv", unsetenv_msk},
	    {"exit", quit},
	    /*{"donut", donut},*/
	    {"env", print_env},
	    {NULL, NULL}};
	int i;

	for (i = 0; func[i].cmdname; i++)
	{
		if (_strcmp(cmd, func[i].cmdname) == 0)
			break;
	}
	return (func[i].f);
}

/**
 * setenv_msk - Calls _setenv() with the suitable arg list.
 * @args: Argument list to resolve.
 * Return: Returns the exit status of the command.
 */
int setenv_msk(char **args)
{
	int ret;

	ret = _setenv(args[1], args[2], 1);

	return (ret);
}

/**
 * unsetenv_msk - Calls _unsetenv() with the suitable arg list.
 * @args: Argument list to resolve.
 * Return: Returns the exit status of the command.
 */
int unsetenv_msk(char **args)
{
	int ret;

	ret = _unsetenv(args[1]);

	return (ret);
}

/**
 * quit - exits the shell with a call to exit with an exit status status.
 * @status: Argument list to resolve.
 * Return: Returns the exit status of the command.
 */
int quit(char **status)
{
	int flag = 'A';

	if (status[1])
		flag = atoi(status[1]);
	free(*status);
	free_pathlist(path_lt);
	free_env(environ);
	if (flag == 'A')
		exit(0);
	exit(flag);
}
