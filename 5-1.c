/*
 * Exercise 5-1. As written, getint treats a + or - followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  100
#define SIZE     100

/* functions declarations */
int  getch(void);
void ungetch(int);
int  getint(int *);

/* global variable */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */

int getch(void)              /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)          /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))    /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
		return 0;            /* it is not a number */

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		if (!isdigit(c = getch())) {
			ungetch(c);
			return 0;        /* it is not a number */
		}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

int main(void)
{
	int n, i, array[SIZE], input;

	n = 0;
	input = getint(&array[n++]);
	while (n < SIZE && input != EOF) {
		if (input == 0)      /* do not store non-numbers */
			--n;
		input = getint(&array[n++]);
	}
	
	printf("%i\n", n);
 	for (i = 0; i < n - 1; ++i)
		printf("%i ", array[i]);
	printf("\n");

	return 0;
}
