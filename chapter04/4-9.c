/*
 * Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be if an EOF is pushed
 * back, then implement your design. 
 *
 * NOTE: the conversion of EOF (-1) from int to char and back to int may not
 * preserve negative value of EOF on some machines. Thus, we should declare buf[]
 * as int but[] to avoid conversion from from int to char to int of EOF.
 *
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
int    buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* test ungets */
int main(void)
{
	int c;

	ungetch(EOF);
	ungetch('A');
	ungetch('B');
	ungetch('C');
	ungetch('D');

	while ((c = getch()) != EOF)
		putchar(c);
	printf("\n");

	return 0;
}
