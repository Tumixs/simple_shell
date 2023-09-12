/*
 * Simple_shell: shell.c
 * Author: Asere Oluwtumise .S
 */
#include "common.h"
#include "path.h"
void handler(int sig);
/**
 * main - Program start.
 * @ac: No of cmd-line args.
 * @av: Array of cmd-line args.
 * @env: Inherited Environment.
 *
 * Return: Always 0.
 */
int main(UNUSED int ac, UNUSED char **av, char **env)
{
	char *cmd = NULL, *token = NULL;
	size_t len = 0;
	int count, wstatus = 0;
	char *arg[1024] = {0};
	pid_t mypid;
	char *dir = NULL;
	path *path_lt;
	int hist = 0;

	if (signal(SIGINT, handler) == SIG_ERR)
		return (-1);
	path_lt = build_pathlist();
	if (path_lt == NULL)
	{
		write(STDERR_FILENO, "failed to build path\n", 21);
		return (-1);
	}
	write(STDIN_FILENO, "$ ", 2);
	while ((_getline(&cmd, &len, stdin)) != -1)
	{
		hist++;
		cmd[strlen(cmd) - 1] = '\0';
		if ((arg[0] = _strtok(cmd, " ")) == NULL)
		{
			write(STDOUT_FILENO, "$ ", 3);
			continue;
		}
		for (count = 1;; count += 1)
		{
			token = _strtok(NULL, " ");
			if (token == NULL)
			{
				arg[count] = NULL;
				break;
			}
			arg[count] = token;
		}
		arg[count + 1] = NULL;
		dir = getcmdpath(arg[0], path_lt);
		if (dir == NULL)
		{

			dprintf(STDERR_FILENO, "%s: %d: %s: not found", av[0], hist, arg[0]);
			write(STDOUT_FILENO, "\n$ ", 3);
			free(cmd);
			cmd = NULL;
			continue;
		}
		mypid = fork();
		if (mypid == 0)
		{
			if ((execve(dir, arg, env)) == -1)
			{
				dprintf(STDERR_FILENO,
					"%s: %d: %s: Permission denied\n",
					av[0], hist, arg[0]);
				return (EXIT_FAILURE);
			}
			else
				return (EXIT_SUCCESS);
		}
		else
		{
			wait(&wstatus);
			if (WIFSIGNALED(wstatus))
				if (WTERMSIG(wstatus) == SIGINT)
					continue;
			write(STDOUT_FILENO, "$ ", 3);
			free(cmd);
			free(dir);
			dir = NULL;
			cmd = NULL;
		}
		/* else */
		/* wait(&wstatus); */
	}
	putchar('\n');
	free(cmd);
	free(dir);
	free_pathlist(path_lt);
	return (0);
}

/**
 * handler - Handles the SIGINT signal.
 * Description: Enables the shell to ignore SIGINT by printing a propmt instead
 * @sig: Caught signal.
 */
void handler(UNUSED int sig)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
