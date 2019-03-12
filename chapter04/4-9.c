/*
 * Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be if an EOF is pushed
 * back, then implement your design. 
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE     100

/* functions */
int    getch(void);
void   ungetch(int);
void   ungets(char []);

/* globals */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */
int    pushedEOF;            /* signals EOF has been pushed-back */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : (pushedEOF) ? EOF : getchar();
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (c == EOF) {
		pushedEOF = 1;
		return;
	}

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* test ungets */
int main(void)
{
	int c;

	ungetch('A');
	ungetch('B');
	ungetch('C');
	ungetch('D');
	ungetch(EOF);

	while ((c = getch()) != EOF)
		putchar(c);
	printf("\n");

	return 0;
}
