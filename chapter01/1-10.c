/*
 * Exercise 1-10. Write a program to copy its input to its output, replacing
 * each tab by \t, each backspace by \b, and each backslash by \\. This makes
 * tabs and backspaces visible in an unambiguous way.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define YES 1
#define NO  0 

int main(void)
{
	int c, charReplaced; 

	while ((c = getchar()) != EOF) {
		charReplaced = NO;
		if (c == '\t') {
			printf("\\t");
			charReplaced = YES;
		}
		if (c == '\b') {
			printf("\\b");
			charReplaced = YES;
		}
		if (c == '\\') {
			printf("\\\\");
			charReplaced = YES;
		}
		if (charReplaced == NO)
			putchar(c);
	}
	return 0;
}
