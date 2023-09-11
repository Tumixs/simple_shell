/*
 * File: shell.c
 * Author: Asere Oluwtumise .S
 */
#include "main.h"
int main(UNUSED int ac, UNUSED char **av, char **env)
{
	char *cmd, *token;
	size_t len;
	/* int wstatus; */
	int count, wstatus = 0;
	char *arg[1024];
	pid_t mypid;
	/* char *prompt = "$ ";*/
	/* write(STDIN_FILENO, prompt, 2);*/

	printf("$ ");
	while ((_getline(&cmd, &len, stdin)) != -1)
	{
		cmd[strlen(cmd) - 1] = '\0';
		arg[0] = _strtok(cmd, " ");
		for (count = 1;; count += 1)
		{
			token = _strtok(NULL, " ");
			if (token == NULL)
				break;
			arg[count] = token;
		}
		arg[count + 1] = NULL;

		mypid = fork();
		if (mypid == 0)
		{
			if ((execve(arg[0], arg, env)) == -1)
			{
				dprintf(STDERR_FILENO, "%s: command not found\n", arg[0]);
				free(cmd);
				return (EXIT_FAILURE);
			}
			free(cmd);
			return (EXIT_SUCCESS);
		}
		else
		{
			wait(&wstatus);
			printf("$ ");
		}
		/* else */
		/* wait(&wstatus); */ }
		free(cmd);

		return (0);
}
