/*
 * File: strtok.c
 * Author: Asere Oluwatumise.c
 */
#include "common.h"
/**
 * _strtok - Breaks a string into tokens.
 * @str: String to break
 * @delim: Delimiter
 *
 * Return: Returns a pointer to a null terminated string
 *	containing the next token.
 */
char *_strtok(char *str, const char *delim)
{
	static char *nxtbyte;
	char *token = NULL;

	if (str != NULL)
		nxtbyte = str; /* Stores string perm */
	if (nxtbyte == NULL || *nxtbyte == '\0')
		return (NULL);
	token = nxtbyte;

	while (*(nxtbyte++))
	{
		if (*nxtbyte == '\0')
		{
			nxtbyte = NULL;
			return (token);
		}
		if (*nxtbyte == *delim)
			break;
	}
	*nxtbyte = '\0';
	while (*nxtbyte++)
	{
		if (*(nxtbyte) == *delim)
			nxtbyte++;

		if (*(nxtbyte) == '\0')
			return (NULL);
	}

	return (token);
}
