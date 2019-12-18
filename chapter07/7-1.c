/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * argv[0].
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* parsename: if program name starts with '.', parse it, i.e. trim the full
 * pathname and return name only, otherwise return name as is. */
char *parsename(char *name)
{
	return name[0] == '.' ? strrchr(name, '/') + 1 : name;
}

int main(int argc, char *argv[])
{
	int c;
	int (*func)(int);  /* function pointer to tolower or toupper */
	char *prog;        /* program name */

	--argc;
	prog = parsename(argv[0]);
	if (!strcmp("tolower", prog))
		func = tolower;
	else if (!strcmp("toupper", prog))
		func = toupper;
	else {
		printf("Error: rename program to tolower or toupper\n");
		return -1;
	}
	while ((c = getchar()) != EOF)
		putchar(func(c));
	return 0;
}
