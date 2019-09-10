/*
 * Exercise 5-2. Write getfloat, the floating-point anolog of getint. What type
 * does getfloat return as its function value? int
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  100
#define SIZE     100

/* functions */
int  getch(void);
void unget(int);
int  getfloat(double *);

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

/* getfloat: get next float from input into *pn */
int getfloat(double *pn)
{
	int c, sign, signChar, decimalPoint = 1;

	while (isspace(c = getch()))    /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
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
	if (c == '.')
		while (isdigit(c = getch())) {
			decimalPoint *= 10; 
			*pn += (double) (c - '0') / decimalPoint;
		}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main(void)
{
	int n, input;
	double array[SIZE];

	for (n = 0; n < SIZE && (input = getfloat(&array[n])) != EOF; ++n) {
		if (input == 0 || input == '-' || input == '+')
			break;
		printf(" %g", array[n]);
	}
	printf("\n");
	return 0;
}
