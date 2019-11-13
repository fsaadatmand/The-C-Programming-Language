/*
 * Exercise 5-2. Write getfloat, the floating-point anolog of getint. What type
 * does getfloat return as its function value?
 *
 * By Faisal Saadatmand
 */

/*
 * Answer: It should return an int, which then could be used to check if the
 * operation was successful or not or if the EOF was reached. See main
 * function.
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  100

/* functions */
int  getch(void);
void unget(int);
int  getfloat(double *);

/* global */
int buf[BUFSIZE];         /* buffer from ungetch (can handle EOF push back) */
int bufp = 0;             /* next free position in buf */

int getch(void)           /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)       /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getfloat: get next float from input into *pn */
int getfloat(double *pn)
{
	int c, sign;
	double i;

	while (isspace((c = getch()))) /* skip whitespace */
		;
	if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		if (!isdigit((c = getch()))) /* is the sign is follwed by a digit? */
			return 0; /* it is not a number */
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.')
		for (i = 10.0F; isdigit(c = getch()); i = i * 10.0F)
			*pn += (c - '0') / i;
	*pn *= sign;
	ungetch(c);
	return c;
}

int main(void)
{
	int input;
	double num;

	while ((input = getfloat(&num)) && input != EOF)
		printf("%g\n", num);

	return 0;
}
