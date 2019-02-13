/*
 * Exercise 5-1. As written, getint treats a + or - followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input. Alternate version using. Perhaps the correct way?
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  100
#define SIZE     100

/* functions */
int  getch(void);
void ungetch(int);
int  getint(int *);

/* globals */
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
	static int skipped;

	if (skipped > 0) {
		pn -= skipped;       /* set the pointer */
	}

	while (isspace(c = getch()))    /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		++skipped;
		return 0;            /* it is not a number */
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		if (!isdigit(c = getch())) {
			ungetch(c);
			++skipped;
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
	int i;                   /* index for printing digits[] */
	int n;                   /* number of read characters */
	int nDigits;             /* number of read and stored digits */
	int nextDigit;           /* next input digit */
	int nonNumbers;          /* skipped non-number characters */
	int numbers[SIZE];       /* stored numbers */

	n = nonNumbers = 0;
	nextDigit = getint(&numbers[n++]);
	while (n < SIZE && nextDigit != EOF) {
		if (nextDigit == 0)
			++nonNumbers;
		nextDigit = getint(&numbers[n++]);
	}

	nDigits = (n - 1) - nonNumbers;
	for (i = 0; i < nDigits; ++i)
		printf("%i ", numbers[i]);
	printf("\n");

	return 0;
}
