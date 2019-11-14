/* 
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C
 * comments don't nest.
 *
 * By Faisal Saadatmand
 */

/* 
 * NOTE: In keeping with the C standard the book follows, this program does not
 * delete single-line comments, i.e. lines beginning with //, because their
 * addition into the language came after ANSI C (C89).
 */

#include <stdio.h>

#define IN 1
#define OUT 0

/* isQuotationMark: return true if c is a valid beginning (or end) of a string
 * literal, otherwise return 0 */
int isQuotationMark(char prev, char c)
{
	return prev != '\\' && prev != '\'' && c == '\"';
}

int main(void)
{
	int prevC; /* previously read character from input */
	int c; /* currently read character from input */
	int comment, quote; /* flag variables */

	comment = quote = OUT;
	prevC = getchar(); /* get the first character */
	while ((c = getchar()) != EOF) { /* get the next character */
		if (isQuotationMark(prevC, c)) {
			if (quote == IN)
				quote = OUT; /* the end of quote */
			else if (comment == OUT)
				quote = IN; /* the beginning of a quote */
		}
		if (quote == OUT && prevC == '/' && c == '*')
			comment = IN; /* the beginning of a comment */
		if (comment == OUT)
			putchar(prevC); /* print previously read character */
		if (comment == IN && prevC == '*' && c == '/') {
			c = getchar(); /* skip '/' character */
			comment = OUT; /* the end of a comment */
		}
		prevC = c; /* store c */
	}
	putchar(prevC); /* print the last previously read character */
	return 0;
}
