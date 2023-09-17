#include <stdio.h>
#include "env.h"
#include <string.h>
#include "common.h"
int main(void)
{
	char **new_environ;

	/* 1 */
	/* DOC */
	printf("Building environment\n");
	fflush(NULL);
	/* Action */
	new_environ = build_env(NULL, NULL); /* Check  if build_env fails */
	if (!new_environ)
		exit(-1);
	environ = NULL;
	environ = new_environ;
	/* OUT */
	printf("Printing environment:\n");
	fflush(NULL);
	print_env();
	printf("End of test 1 \n\n");
	fflush(NULL);

	/* 2 */
	/* DOC */
	printf("\nTesting `_setenv`: \n");
	printf("Doing:\n"
	"_setenv(AUTHOR, ASERE OLUWATUMISE & OLADOSUADEBISI, 2)\n"
	"_setenv(AUTHOR=, ASERE OLUWATUMISE & OLADOSU ADEBISI, 2)\n"
	"_setenv(USER, ASERE OLUWATUMISE & OLADOSU ADEBISI, 2)\n");
	fflush(NULL);
	/* Action */
	_setenv("AUTHOR", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	_setenv("AUTHOR=", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	_setenv("USER", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	/* OUT */
	printf("Printing environment:\n");
	fflush(NULL);
	print_env();
	printf("End of test 2\n\n");
	fflush(NULL);


	/* 3 */
	/*DOC */
	printf("Doing:\n _unsetenv(AUTHOR)\n");
	fflush(NULL);
	/* Action */
	_unsetenv("AUTHOR");
	/* OUT */
	printf("Printing environment:\n");
	fflush(NULL);
	print_env();
	printf("End of test 3\n\n");
	fflush(NULL);

	/* 4 */
	/* Doc */
	printf("Doing: \n"
	"_setenv(AUTHOR, ASERE OLUWATUMISE & OLADOSU ADEBISI, 2)\n"
	"_setenv(AUTHOR=, ASERE OLUWATUMISE & OLADOSU ADEBISI, 2)\n"
	"_setenv(USER, ASERE OLUWATUMISE & OLADOSU ADEBISI, 2)\n"
	"_unsetenv(USER)\n");
	fflush(NULL);
	/* Action */
	_setenv("AUTHOR", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	_setenv("AUTHOR=", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	_setenv("USER", "ASERE OLUWATUMISE" & "OLADOSU ADEBISI", 2);
	_unsetenv("USER");
	/* OUT */
	printf("Printing environment:\n");
	fflush(NULL);
	print_env();
	printf("End of test 4\n\n");
	fflush(NULL);	free_env(environ);

	return (0);
}
