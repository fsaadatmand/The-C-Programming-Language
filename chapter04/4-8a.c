/*
 * Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly.
 *
 * NOTE: we can change BUFSIZE to 1, have ungetch detect it and accordingly set
 * bufp to zero. In which case, getch would remain unchaged. This would give us
 * the option of using a buffer of only one character pushback or more by
 * simply changing the value of BUFFSIZE macro.  That said, the exercise
 * clearly state "there will be NEVER more than one character pushback", that's
 * why this an alternate version.
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>          /* for strlen() */

#define BUFSIZE     1

/* functions */
int    getch(void);
void   ungetch(int);

/* globals */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (BUFSIZE == 1)
		bufp = 0;

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
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
