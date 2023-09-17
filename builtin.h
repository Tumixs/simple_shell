#ifndef BUILTIN_H
#define BUILTIN_H

typedef int(*insider)(char **);
typedef struct builtin
{
	char *cmdname;
	int (*f)(char** args);
}builtin;
int runbuiltin(char **arg);
int (*getbuiltin(char *cmd))(char **args);
int quit(char **status);
int cd(char **pathname);
int setenv_msk(char **args);
int unsetenv_msk(char **args);
int donut(char **args);
/*int print_env(UNUSED char **args);*/


#endif
