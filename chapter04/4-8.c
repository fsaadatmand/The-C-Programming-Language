/*
 * Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly.
 *
 * Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
int    getch(void);
void   ungetch(int);

/* globals */
int    buf;                 /* buffer from ungetch */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	int c;

	if (buf) {
		c = buf;
	} else
		c = getchar();
	buf = 0;
	return c;
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (buf)
		printf("ungetch: too many characters\n");
	else
		buf = c;
}

/* test getch */
int main(void)
{
	ungetch('A');
	ungetch('B');                      /* should give error */
	printf ("%c\n", getch());
	ungetch('C');
	printf ("%c\n", getch());

	return 0;
}
