/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * argv[0].
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int c, function;
	char *pname;                       /* program name */

	if (argc != 1)
		return -1;

	pname = (strrchr(*argv, '/')) + 1; /* parse program name */

	if (strcmp("tolower", pname) == 0)
		function = 0;
	else if (strcmp("toupper", pname) == 0)
		function = 1;
	else {
		printf("%s: Unknown function: ", pname);
		printf("Rename program to tolower or toupper.\n");
		return -1;
	}
	while ((c = getchar()) != EOF)
		putchar((function) ? toupper(c) : tolower(c)); 
	return 0;
}
