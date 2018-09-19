/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank.
 * By Faisal Saadatmand
*/

#include <stdio.h>

#define YES 1
#define NO  0

int main(void)
{
	int c;          /* current input character */
	int blank;      /* flag for the status of the previous character */

	blank = NO;     /* perhaps unnecessary */
	while ((c = getchar()) != EOF) {
		if (c != ' ')
			blank = NO;
		if (!blank)
			putchar(c);
		if (c == ' ')
			blank = YES;
	}
	return 0;
}

