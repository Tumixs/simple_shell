/*
 * Environment methods
 * Author: Asere Oluwatumise S.
 */

/* setenv() and unsetenv() are not compliant with task declaration. */
/* They are compliant with the glibc */

#include "common.h"
#include "env.h"

/**
 * build_env - Builds a list/array of the environment.
 * Description: The environment is COPIED from the inherited global `environ`.
 * @append: If append is not NULL, it is appended to the created environment.
 * @remove: If remove is not NULL, it is omitted during creation.
 * Return: Returns a pointer to built environment.
 */
char **build_env(const char *append, const char *remove)
{
	char **env_copy = NULL, *tmp = NULL;
	int i, len, j, del = 1;

	for (len = 0; environ[len]; len++)
		;
	if (append != NULL)
		len += 1;
	if (remove != NULL)
		len -= 1;
	env_copy = malloc((++len) * sizeof(char *));
	if (env_copy == NULL)
		return (NULL);
	env_copy[len - 1] = NULL;
	for (i = 0, j = 0; environ[i]; i++)
	{
		if (remove)
		{
			del = _strncmp(environ[i], remove, _strlen(remove));
			if (del == 0)
				continue;
		}
		tmp = malloc((_strlen(environ[i]) + 1) * sizeof(char));
		if (tmp == NULL)
		{
			free_env(env_copy);
			return (NULL);
		}
		_strcpy(tmp, environ[i]);
		env_copy[j] = tmp;
		j++;
		tmp = NULL;
	}
	if (append)
	{
		tmp = malloc((_strlen(append) + 1) * sizeof(char));
		_strcpy(tmp, append);
		env_copy[len - 2] = tmp;
		tmp = NULL;
	}
	return (env_copy);
}

/**
 * _getenv - Gets an enviroment variable.
 *
 * @name: Name of env varaible
 * Return: Returns the value of the variable
 */
char *_getenv(const char *name)
{
	int i;

	for (i = 0; environ[i]; i++)
		if (!_strncmp(environ[i], name, _strlen(name)))
			return (environ[i]);
	return (NULL);
}

/**
 * free_env - Frees the environment.
 * @env: Global to free.
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
		if (env[i])
			free(env[i]);
	free(env);
}
/**
 * _setenv - Attempts to add a new value to the environment.
 * @name: Name of environment.
 * @value: Value.
 * @overwrite: Flag.
 *
 * Return: Returns 0 on success, otherwise -1.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *new = NULL, **old = NULL, **new_environ = NULL;

	if (!name)
		return (-1);
	if (!value)
		return (-1);
	/* Not required by ALX checker */
	if (_strchr(name, '=') || _strchr(value, '='))
	{
		write(STDERR_FILENO, "Error: name cannot contain an =\n", 32);
		return (-1);
	}
	new = malloc((_strlen(name) + _strlen(value) + 2) * sizeof(char));
	if (new == NULL)
		return (-1);
	_strcpy(new, name);
	_strcat(new, "=");
	if (value)
		_strcat(new, value);
	/* Check if new exists in current environ */
	old = _getenvaddr(name);
	if (old != NULL)
	{
		if (overwrite)
		{
			free((*old));
			(*old) = NULL;
			(*old) = new;
		}
		return (0);
	}
	/* env does not exist before. Append to a newly created environ */
	new_environ = build_env(new, NULL);
	free(new);
	if (new_environ == NULL)
		return (-1);
	free_env(environ);
	environ = NULL;
	environ = new_environ;
	return (0);
}

/**
 * _unsetenv - UNsets an environment variable.
 * @name: Name of environment.
 *
 * Return: Retur2ns 0 on success, otherwise -1.
 */
int _unsetenv(const char *name)
{
	char **new = NULL;

	if (_getenv(name) != NULL)
	{
		new = build_env(NULL, name);
		if (new == NULL)
			return (-1);
		free_env(environ);
		environ = NULL;
		environ = new;
	}
	return (0);
}
