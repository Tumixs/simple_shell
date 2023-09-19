/**
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
 * cmd: Builtin identifier.
 *
 * Return: Returns the function poinetr, otherwise NULL if it exist's not.
 */
int (*getbuiltin(char *cmd))(char **cmd)
{
	builtin func[] =
	{
		{"cd", cd},
		{"setenv", setenv_msk},
		{"unsetenv", unsetenv_msk},
		{"exit", quit},
		/*{"donut", donut},*/
		{"env", print_env},
		{NULL, NULL}
	};
	int i;

	for (i = 0; func[i].cmdname; i++)
	{
		if (strcmp(cmd, func[i].cmdname) == 0)
			break;
	}
	return (func[i].f);

}
/**
 * cd - Changes the working directory.
 * @path: Pathname.
 */
int cd(char **path)
{
	char *pathname = path[1];
	char *oldpwd = NULL;
	char *newpwd = NULL;
	int stat = -1;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);
	if (!pathname)
	{
		pathname = _getenv("HOME");
		stat = chdir(pathname + 5);
		if (stat == -1)
		{
			write(STDERR_FILENO, "FAILED\n", 7);
			return (-1);
		}
		newpwd = getcwd(newpwd, 0);
		if (!newpwd)
			return (-1);
	}
	else if (strncmp("-", pathname, 1) == 0)
	{
		pathname = _getenv("OLDPWD");
		stat = chdir(pathname + 7);
		if (stat == -1)
		{
			write(STDERR_FILENO, "FAILED to go back\n", 17);
			return (-1);
		}
		newpwd = getcwd(newpwd, 0);
		if (!newpwd)
			return (-1);
	}
	else 
	{
		stat = chdir(pathname);
		if (stat == -1)
		{
			write(STDERR_FILENO, "FAILED to chidr\n", 16);
			return (-1);
		}
		newpwd = getcwd(newpwd, 0);
		if (!newpwd)
			return (-1);
	}
	_setenv("OLDPWD", oldpwd, 1);
	_setenv("PWD", newpwd, 1);
	free(oldpwd);
	free(newpwd);
	return (0);

}
/**
 * setenv_msk - Calls _setenv() with the suitable arg list.
 * @args: Argument list to resolve.
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
 */
int unsetenv_msk(char **args)
{
	int ret;
	ret = _unsetenv(args[1]);

	return (ret);
}

/**
 * quit - exits the shell with a call to exit with an exit status status.
 * @args: Argument list to resolve.
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
