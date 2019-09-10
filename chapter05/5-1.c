/*
 * Exercise 5-1. As written, getint treats a + or - followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input.
 *
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

/* global */
int    buf[BUFSIZE];         /* buffer from ungetch */
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
	int c, sign, signChar;

	while (isspace(c = getch()))    /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
		return 0;            /* it is not a number */
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		signChar = c;
		if (!isdigit(c = getch())) {
			if (c != EOF)
				ungetch(c);
			ungetch(signChar);
			return signChar;
		}
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
	int array[SIZE], input;
	size_t n;

	for (n = 0; n < SIZE && (input = getint(&array[n])) != EOF; ++n) {
		if (input == 0 || input == '-' || input == '+')
			break;
		printf(" %i", array[n]);
	}
	printf("\n");
	return 0;
}
