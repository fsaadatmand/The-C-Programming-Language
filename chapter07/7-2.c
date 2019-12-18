/*
 * Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines.
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>

#define MAXLEN  80 
#define NCHAR   6  /* number of actually printed characters */

/* inclen: increment line's length by the number of actually printed
 * characters. Break the line if its too long. */
int inclen(int len, int n)
{
	if ((len += n) < MAXLEN)
		return len;
	printf("\n");
	return n;
}

int main(void)
{
	int c;
	int len; /* length of currently read line */

	len = 0;
	while ((c = getchar()) != EOF)
		if (!isgraph(c)) {
			printf(" 0x%02o ", c); /* replace by NCHAR hex characters */
			len = inclen(len, NCHAR); 
			if (c == '\n') {
				printf("\n");   /* break the line */
				len = 0;
			}
		} else { /* graphical character */
			printf("%c", c);
			len = inclen(len, 1);
		}
	return 0;
}
