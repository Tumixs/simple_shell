/*
 * Linked list structure for environment PATH.
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
#include "path.h"
#include "env.h"

/**
 * print_pathlist - prints each path in linked list
 * @head: first node
 */
void print_pathlist(path *head)
{
	if (head == NULL)
		return;
	while (head != NULL)
	{
		printf("%s\n", head->pathname);
		head = head->next;
	}
}

/**
 * free_pathlist - frees linked list of paths
 * @head: first node: first node
 */
void free_pathlist(path *head)
{
	path *nxt_node;

	if (head == NULL)
		return;
	while (head != NULL)
	{
		nxt_node = head->next;
		if (head->pathname)
			free(head->pathname);
		free(head);
		head = NULL;
		head = nxt_node;
	}
}

/**
 * append_path - appends a pathname to a list of `PATHS`
 * @head: first node
 * @pathname: Name of path or directory
 *
 * Return: returns a pointer to the head of the modified linked list
 */
path *append_path(path *head, char *pathname)
{
	path *nxt_node;
	path *dup;

	if (head == NULL)
	{
		head = malloc(sizeof(path));
		if (head == NULL)
			return (NULL); /* err_handle*/
		head->pathname = malloc(sizeof(char) * (strlen(pathname) + 1));
		if (head->pathname == NULL)
			return (NULL);
		/*head->pathname = pathname;*/
		strcpy(head->pathname, pathname);
		head->next = NULL;
		return (head);
	}

	for (dup = head, nxt_node = dup->next; (dup->next != NULL); dup = nxt_node)
		nxt_node = dup->next;
	nxt_node = malloc(sizeof(path));
	if (nxt_node == NULL)
		return (NULL); /* err_handle*/
	nxt_node->pathname = malloc(sizeof(char) * (strlen(pathname) + 1));
	if (nxt_node->pathname == NULL)
		return (NULL);
	/*nxt_node->pathname = pathname;*/
	strcpy(nxt_node->pathname, pathname);
	nxt_node->next = NULL;
	dup->next = nxt_node;

	return (head);
}

/**
 * build_pathlist - Builds a linked list of the environment `PATH`
 * Description: Each struct or `node` consist of a pathname and a link  to the
 * next `PATH`.
 * Return: Returns `head` (pointer) to a list of `PATH`.
 */
path *build_pathlist()
{
	char *header, *env_path, *tmp;
	char *token;
	path *head = NULL;

	tmp = _getenv("PATH");
	env_path = malloc(sizeof(char) * (strlen(tmp) + 1));
	if (env_path == NULL)
		return (NULL);
	strcpy(env_path, tmp);
	header = _strtok(env_path, "=");
	if (!header)
		return (NULL);
	while ((token = _strtok(NULL, ":")))
		if ((head = append_path(head, token)) == NULL)
			free_pathlist(head);
	free(env_path);
	return (head);
}

/**
 * getcmdpath - Gets the absolute path of a given shell command.
 * @cmd: Shell/built-in command.
 * @path_lt: linked list of path.
 *
 * Return: Returns the absolute path of cmd, if it exists.
 */
char *getcmdpath(char *cmd, path *path_lt)
{
	char *dir = NULL;
	struct stat st;
	int i = strlen(cmd);
	int j = 0;
	path *path_copy = path_lt;

	/*UNUSED path *next;*/
	while (path_copy != NULL)
	{

		j = strlen(path_copy->pathname);
		dir = malloc((i + j + 2) * (sizeof(char))); /* extra 1 for the slash */
		if (dir == NULL)
		{
			perror("path malloc\n");
		}
		strcpy(dir, path_copy->pathname);
		strcat(dir, "/");
		strcat(dir, cmd);
		if (stat(dir, &st) == 0)
			return (dir);
		path_copy = path_copy->next;
		free(dir);
		dir = NULL;
	}
	return (NULL);
}
