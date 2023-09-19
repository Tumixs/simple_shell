/*
 * simple_shell: test_strtok.c
 * Author: Asere Oluwatumise .S
 * -- Comparing standard lib strtok() to custom _strok() --
 */
#include "common.h"
void __attribute__((constructor)) strtok_test(void);
/**
 * strtok_test
 */
void __attribute__((constructor)) strtok_test(void)
{
	char str1[] = "I really love programming";
	char str2[] = "I really love programming";
	char str3[] = "         love            ";
	char str4[] = "         love            ";
	char str5[] = "aaa;,bbb,";
	char str6[] = "aaa;,bbb,";
	char *token1 = NULL;
	char *token2 = NULL;

	printf("\n(1) TEST-STRING: %s | delim:\" \"", str1);
	/* (1) Std lib */
	printf("\nSTD-LIB:\n");
	token1 = strtok(str1, " ");
	printf("%s\n", token1);
	while (token1 != NULL)
	{
		token1 = strtok(NULL, " ");
		if (token1 != NULL)
			printf("%s\n", token1);
	}
	/* (1) custom */
	printf("\nCUSTOM-BUILD:\n");
	token2 = _strtok(str2, " ");
	printf("%s\n", token2);
	while (token2 != NULL)
	{
		token2 = _strtok(NULL, " ");
		if (token2 != NULL)
			printf("%s\n", token2);
	}
	/* --- TEST 2 --- */
	printf("\n(2) TEST-STRING: %s | delim:\" \"", str3);
	/* (2) Std lib */
	printf("\nSTD-LIB:\n");
	token1 = strtok(str3, " ");
	printf("%s\n", token1);
	while (token1 != NULL)
	{
		token1 = strtok(NULL, " ");
		if (token1 != NULL)
			printf("%s\n", token1);
	}
	/* (2) custom */
	printf("\nCUSTOM-BUILD:\n");
	token2 = _strtok(str4, " ");
	printf("%s\n", token2);
	while (token2 != NULL)
	{
		token2 = _strtok(NULL, " ");
		if (token2 != NULL)
			printf("%s\n", token2);
	}
	/* --- TEST 3 --- */
	printf("\n(3) TEST-STRING: %s | delim:\";,\"", str5);
	/* (3) Std lib */
	printf("\nSTD-LIB:\n");
	token1 = strtok(str5, ";,");
	printf("%s\n", token1);
	while (token1 != NULL)
	{
		token1 = strtok(NULL, ";,");
		if (token1 != NULL)
			printf("%s\n", token1);
	}
	/* (2) custom */
	printf("\nCUSTOM-BUILD:\n");
	token2 = _strtok(str6, ";,");
	printf("%s\n", token2);
	while (token2 != NULL)
	{
		token2 = _strtok(NULL, ";,");
		if (token2 != NULL)
			printf("%s\n", token2);
	}
}

/**
 * main - Program start
 *
 * Return: always 0
 */
int main(void)
{
	return (0);
}
