/*
 * Exercise 5-2. Write getfloat, the floating-point anolog of getint. What type
 * does getfloat return as its function value? Integer
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  100
#define SIZE     100

int  getch(void);
void unget(int);
int  getfloat(double *);

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

/* getfloat: get next float from input into *pn */
int getfloat(double *pn)
{
	int c, sign, decimalPoint = 1;

	while (isspace(c = getch()))    /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
		return 0;            /* it is not a number */

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		if (!isdigit(c = getch())) {
			ungetch(c);
			return 0;        /* it is not a number */
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
	int n, i, input;
	double array[SIZE];

	n = 0;
	input = getfloat(&array[n++]);
	while (n < SIZE && input != EOF) {
		if (input == 0)      /* do not store non-numbers */
			--n;
		input = getfloat(&array[n++]);
	}
	
	for (i = 0; i < n - 1; ++i)
		printf("%g ", array[i]);
	printf("\n");

	return 0;
}
