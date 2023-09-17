#include "string.h"

int _strlen(char *s)
{
	int i = 0;
	
	for( i = 0; s[i]; i++)
		;
	return (i);
}
