/*
 * Environment methods
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
#include "env.h"
/**
 * _getenv - Gets an enviroment variable.
 *
 * @name: Name of env varaible
 * Return: Returns the value of the variable
 */
char *_getenv(char *name)
{
	int i;

	for (i = 0; environ[i]; i++)
		if (!strncmp(environ[i], name, strlen(name)))
			return (environ[i]);
	return (NULL);
}
