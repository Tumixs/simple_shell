#ifndef MAIN_H
#define MAIN_H
/*
 * simple_shell: main.h
 * Author: Asere Oluwatumise .S
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define UNUSED __attribute__((unused))

ssize_t _getline(char **line, size_t *len, FILE *stream);
char *_strtok(char *str, const char *delim);

#endif
