/*
 * Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines.
 *
 * By Faisal Saadatmand
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLENGTH 81

int main(void)
{
	char c;
	int len;                           /* length of currently read line */

	for (len = 0; (c = getchar()) != EOF; len++) {
		if (len == MAXLENGTH) {        /* simple line breaking */
			printf("\n");
			len = 0;
		}
		if (!isgraph(c))              /* print in hexadecimal */
			printf("%x", c);
		else
			printf("%c", c);
	}
	printf("\n");
	return 0;
}
