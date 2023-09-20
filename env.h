#ifndef ENV_H
#define ENV_H
/*
 * Defualt environment methods
 * Author: Asere Oluwatumise S.
 */

/* Default Global environment */
extern char **environ;
char **build_env(const char *, const char *);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);
char **_getenvaddr(const char *name);
int print_env(UNUSED char **env);
void free_env(char **);

#endif
