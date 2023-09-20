/*
 * Environment methods
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
#include "env.h"

/**
 * _getenvaddr - Gets an enviroment variable.
 *
 * @name: Name of env varaible
 * Return: Returns the address of the variable
 */
char **_getenvaddr(const char *name)
{
	char **env_ptr = environ;

	for (; *env_ptr; env_ptr++)
		if (!_strncmp((*env_ptr), name, _strlen(name)))
			return (env_ptr);
	return (NULL);
}

/**
 * print_env - Prints the environment.
 * @env: Environment global.
 * Return: Always 0.
 */
int print_env(UNUSED char **env)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDIN_FILENO, environ[i], _strlen(environ[i]));
		write(STDIN_FILENO, "\n", 1);
	}
	return (0);
}
