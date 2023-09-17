/*
 * Defualt environment methods
 * Author: Asere Oluwatumise S.
 */
#ifndef ENV_H
#define ENV_H

/* Default Global environment */
extern char **environ;
char **build_env(const char *, const char *); /* Create array or a list of the current environ */
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);
char **_getenvaddr(const char *name); /* Gets the direct address of the environ varaible */
int print_env(UNUSED char **env); /* env */
void free_env(char **);

#endif
