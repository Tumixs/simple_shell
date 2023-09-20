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
	static int counter;
	int i;
	char *token = NULL;

	if (str != NULL)
	{
		nxtbyte = str; /* Stores string perm */
		counter = 0;
	}
	i = counter;
	if (nxtbyte == NULL || *nxtbyte == '\0')
		return (NULL);
	for (; nxtbyte[i]; i++) /* mov to first valid token */
	{
		if (!_strchr(delim, nxtbyte[i]))
		{
			token = (nxtbyte + i);
			break;
		}
		else
			nxtbyte[i] = '\0';
	}
	for (; nxtbyte[i]; i++) /* Scan fwd till nxt delim */
	{
		if (nxtbyte[i] == '\0')
		{
			nxtbyte = NULL;
			counter = i;
			return (token);
		}
		if (_strchr(delim, nxtbyte[i]))
		{
			nxtbyte[i] = '\0';
			i++;
			break;
		}
	}
	counter = i;
	return (token);
}
