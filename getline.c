/*
 * File: getline.c
 * Author: Asere Oluwatumise S.
 */
#include "common.h"
/**
 * _getline - Gets a line of text.
 * @line: Pointer to buffer holding text.
 * @len: Number of bytes read.
 * @stream: Where to read text from.
 *
 * Return: Returns the number of characters read excluding the terminating
 * null byte.
 * On failure to read a line or end-of-file condition returns -1
 *
 * If lineptr is set to NULL, automatically allocates buffer to store text
 * otherwise, lineptr can contain a pointer to a malloc-alloacted buffer of
 * *n bytes in size. If buffer is not large enough, _getline resizes it with
 * realloc and updates *lineptr and *n accordingly.
 */
ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	int size = 120;
	size_t count = 0;
	int c;
	char *tmp;

	if (stream == NULL)
		return (-1);
	if ((*line) == NULL)
	{
		(*line) = (char *)malloc(sizeof(char) * size);
		if ((*line) == NULL)
		{
			dprintf(STDERR_FILENO, "Failed to malloc");
			exit(EXIT_FAILURE);
		}
		*len = size;
	}
	while ((c = fgetc(stream)))
	{
		if (feof(stream))
			return (-1);
		if (count == (*len) - 2)
		{
			(tmp) = realloc(*line, sizeof(char) * ((*len) *= 2));
			*line = tmp;
		}
		(*line)[count] = c;
		count += 1;
		if (c == '\n')
		{
			(*line)[count] = '\0';
			*len = count;
			return (count);
		}
	}
	return (-1);
}
