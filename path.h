#ifndef PATH_H
#define PATH_H
/*
 * path methods
 * Author: Asere Oluwatumise S.
 */

/**
 * struct path - A `PATH` struct for the process environment object `PATH`.
 * Description: Use to create list of environment `PATH`
 * @pathname: Directory
 * @next: Next node
 */
typedef struct path
{
	struct path *next;
	char *pathname;
} path;

path *path_lt;
path *build_pathlist();
path *append_path(path *head, char *pathname);
void free_pathlist(path *head);
void print_pathlist(path *head);
char *getcmdpath(char *cmd, path *path_lt);

#endif
