#ifndef ALIAS_H
#define ALIAS_H
/**
 * struct alias_s - ALIAS structure
 * @name: Name of alias.
 * @value: Alias value.
 * @next: Next Alias.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_s;

extern alias_s *alias_g;
alias_s *append(char *name, char *value);
int print_alias(void);
#endif
