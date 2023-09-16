/*
 * Environment methods
 * Author: Asere Oluwatumise S.
 */
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
	{
		write(STDERR_FILENO, "Error: failed to get environment\n", 33);
		return (NULL);
	}
	env_copy[len - 1] = NULL;
	for (i = 0, j = 0; environ[i]; i++)
	{
		if (remove)
		{
			del = strncmp(environ[i], remove, strlen(remove));
			if (del == 0)
				continue;
		}
		tmp = malloc((strlen(environ[i]) + 1) * sizeof(char));
		if (tmp == NULL)
		{
			free_env(env_copy);
			return (NULL);
		}
		strcpy(tmp, environ[i]);
		env_copy[j] = tmp;
		j++;
		tmp = NULL;
	}

	if (append)
	{
		tmp = malloc((strlen(append) + 1) * sizeof(char));
		strcpy(tmp, append);
		env_copy[len - 2] = tmp;
		tmp = NULL;
	}
	return (env_copy);
}

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
		if (!strncmp((*env_ptr), name, strlen(name)))
			return (env_ptr);
	return (NULL);
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
		if (!strncmp(environ[i], name, strlen(name)))
			return (environ[i]);
	return (NULL);
}

/**
 * print_env - Prints the environment.
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDIN_FILENO, environ[i], strlen(environ[i]));
		write(STDIN_FILENO, "\n", 1);
	}
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
	int i;

	if (!name)
		return (-1);
	new = malloc((strlen(name) + strlen(value) + 2) * sizeof(char)); /* 1 for = */
	if (new == NULL)
	{
		write(STDERR_FILENO, "Error: failed to malloc\n", 28);
		return (-1);
	}
	for (i = 0; name[i]; i++)
	{
		if (name[i] == '=')
		{
			write(STDERR_FILENO, "Error: name cannot contain an =\n", 32);
			free(new);
			return (-1);
		}
		new[i] = name[i];
	}
	new[i] = '\0';
	strcat(new, "=");
	strcat(new, value);
	/* Check if new exists in current environ */
	old = _getenvaddr(name);
	if (old != NULL)
	{
		/* env exists. Avoid rewriting the whole array */
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
int _unsetenv(UNUSED const char *name)
{
	char **old = NULL;

	if (_getenv(name) != NULL)
	{
		old = build_env(NULL, name);
		if (old == NULL)
			return (-1);
		free_env(environ);
		environ = NULL;
		environ = old;
	}
	return (0);
}

