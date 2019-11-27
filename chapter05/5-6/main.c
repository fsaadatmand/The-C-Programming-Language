/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 *
 * By Faisal Saadatmand
 */

/*
 * Just use any function listed above in main.c to test its code. Below are
 * some examples.
 *
 * Instructions:
 * To Build:
 * 		make main
 * To run:
 * 		./main
 * To clean object files:
 * 		make clean
 *
 */

#include <stdio.h>
#include "functions.h"


int main(void)
{
	char str[] = "It's not personal";
	const char *pattern = "son";
	char str2[] = "5892";
	int pos, number; 

	/* strindex */
	if ((pos = strindex(str, pattern)) < 0)
		printf("Not found\n");
	else
		printf("%i\n", pos);
	/* reverse */
	reverse(str);
	printf("%s\n", str);
	/* atoi */
	number = atoi(str2);
	printf("%i\n", number);
	printf("%i\n", atoi("4092"));
	return 0;
}
