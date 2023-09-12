/*
 * Defualt environment methods
 * Author: Asere Oluwatumise S.
 */
#ifndef ENV_H
#define ENV_H

void build_env(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(char *name);
void print_env(void);
void free_env(void);

#endif
