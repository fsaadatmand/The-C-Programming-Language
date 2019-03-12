/*
 * Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly.
 *
 * NOTE: see alternate version 4-8a.c
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stddef.h>          /* for NULL */

/* functions */
int    getch(void);
void   ungetch(int);

/* globals */
char    buf;                 /* buffer from ungetch */
char    *bufp = NULL;        /* pointer to buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	char temp;

	if (bufp) {
		temp = *bufp;
		bufp = NULL;
		return temp;
	}
	return getchar();
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (!bufp)
		bufp = &buf;         /* initialize buffer pointer */
	*bufp = c;
}

/* test getch */
int main(void)
{
	ungetch('A');
	ungetch('B');
	ungetch('C');
	ungetch('D');

	putchar(getch());
	printf ("\n");

	return 0;
}
