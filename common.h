#ifndef MAIN_H
#define MAIN_H
/*
 * commons
 * Author: Asere Oluwatumise .S
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define UNUSED __attribute__((unused))

/*char *prompt = "$ ";*/
ssize_t _getline(char **line, size_t *len, FILE *stream);
char *_strtok(char *str, const char *delim);

#endif
