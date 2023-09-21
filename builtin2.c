/*
 * Shell Builtins.
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
#include "builtin.h"
#include "env.h"
#include "path.h"
int cd_home(void);
/**
 * cd - Changes the working directory.
 * @path: Pathname.
 * Return: Returns the exit status of the command.
 */
int cd(char **path)
{
	char *pathname = NULL, *oldpwd = NULL, *newpwd = NULL;
	int stat = -1;

	pathname = path[1];
	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);
	if (!pathname)
	{
		free(oldpwd);
		stat = cd_home();
		if (stat == 0)
			return (0);
		else
			return (-1);
	}
	else if (_strncmp("-", pathname, 1) == 0)
	{
		stat = chdir(_getenv("OLDPWD") + 7);
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
 * cd_home - Changes the working directory to $HOME.
 * Return: Returns the exit status of the command.
 */
int cd_home(void)
{
	char *oldpwd = NULL, *newpwd = NULL;
	int stat = -1;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);
	stat = chdir(_getenv("HOME") + 5);
	if (stat == -1)
	{
		write(STDERR_FILENO, "FAILED\n", 7);
		return (-1);
	}
	newpwd = getcwd(newpwd, 0);
	if (!newpwd)
		return (-1);

	_setenv("OLDPWD", oldpwd, 1);
	_setenv("PWD", newpwd, 1);
	free(oldpwd);
	free(newpwd);
	return (0);
}
