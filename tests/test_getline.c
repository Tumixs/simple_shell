/**
 * Simple_shell: test_getline.c
 * Author: Asere Oluwatumise S.
 * Comapring std-lib getline() with custom build
 */
#include "main.h"
#include <string.h>

int main(void)
{
	char *ptr1 = NULL, *ptr2 = NULL;
	char str1[] = "Hello World!";
	char str2[] = "I am here";
	size_t len1 = 0, len2 = 0;

	/* Test 1 */
	printf("(1)\n");
	printf("std-lib -> Type: \"%s\"\n", str1);
	getline(&ptr1, &len1, stdin);
	printf("Custom -> Type: \"%s\"\n", str1);
	_getline(&ptr2, &len2, stdin);
	printf("std: %s\tlenght: %ld\n", ptr1, len1);
	printf("custom: %s\tlenght: %ld\n", ptr2, len2);
	if ((strcmp(ptr1, ptr2)) != 0)
		printf("Error: string differs!!\n");
	if (strlen(ptr1) != strlen(ptr2))
		printf("Error: Length differs!!\n");

	/* Test 2 */
	printf("(2)\n");
	printf("std-lib -> Type: \"%s\"\n", str2);
	getline(&ptr1, &len1, stdin);
	printf("Custom -> Type: \"%s\"\n", str2);
	_getline(&ptr2, &len2, stdin);
	printf("std: %s\tlenght: %ld\n", ptr1, len1);
	printf("custom: %s\tlenght: %ld\n", ptr2, len2);
	if ((strcmp(ptr1, ptr2)) != 0)
		printf("Error: string differs!!\n");
	if (strlen(ptr1) != strlen(ptr2))
		printf("Error: Length differs!!\n");

	return (0);
}
