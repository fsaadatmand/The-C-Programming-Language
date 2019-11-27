#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/* atoi: convert s to integer (chapter 3) */
int atoi(const char *s)
{
	int n, sign;

	while (isspace(*s)) /* skip whitespace */
		++s;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-') /* skip sign */
		++s;
	for (n = 0; isdigit(*s); ++s)
		n = 10 * n + (*s - '0');
	return sign * n;
}

/* atof: convert string s to double (chapter 4) */
double atof(const char *s)
{
	int sign, expSign;
	double val, power, exponent;

	while (isspace(*s)) /* skip whitespace */
		++s;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		++s;
	for (val = 0.0; isdigit(*s); ++s)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		++s;
	for (power = 1.0; isdigit(*s); ++s) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	if (tolower(*s) == 'e') /* handle scientific notation */
		++s;
	expSign = (*s == '-') ? -1 : 1; /* record  exponent's sign */
	if (*s == '+' || *s == '-')
		++s;
	for (exponent = 0.0; isdigit(*s); s++) /* extract the exponent */
		exponent = 10.0 * exponent + (*s - '0');
	while (exponent-- != 0) /* adjust power according to exponent */
		power = (expSign > 0) ? power / 10: power * 10; 
	return sign * val / power;
}

/* itoa: convert n to characters in s (chapter 3) */
void itoa(int n, char *s)
{
	int sign;

	sign = n; /* record sign */

	do {    /* generate digits in reverse order */
		*s++ = abs(n % 10 + '0'); /* get the next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(s - strlen(s));
}

/* getLine function: read a line into s, return length (chapter 4) */
int getLine(char *s, int lim)
{
	int c;
	char *len;

	len = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return strlen(len);
}

/* getop: get next operator or numeric operand (chapter 4) - getch/ungetch version */
int getop(char *s)
{
	int c;
	char *var;

	while (isblank(s[0] = c = getchar()))
		;
	s[1] = '\0';
	if (c == '-') /* check sign */
		if (!isdigit(*++s = c = getchar())) {
			ungetc(c, stdin);                    
			c = *--s; /* not a sign */
		}
	if (isalpha(c)) { /* string command */
		var = s;
		while (isalpha(*++s = c = getchar()))
			;
		*s = '\0';
		ungetc(c, stdin);
		return (strlen(var) == 1) ? var[0] : NAME;
	}
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	if (isdigit(c))
		while (isdigit(*++s = c = getchar()))
			;
	if( c == '.') /* collect fraction part */
		while (isdigit(*++s = c = getchar()))
			;
	*s = '\0';
	ungetc(c, stdin);
	return NUMBER;
}

/* reverse: reverses the string s in place (chapter 3) */
void reverse(char *s)
{
	char *p, *q, tmp;

	q = s + strlen(s) - 1;
	for (p = s; p < q; ++p, --q) {
		tmp = *p;
		*p = *q;
		*q = tmp;
	}
}

/* strindex: return index of t in s, -1 if none (chapter 4) */
int strindex(const char *s, const char *t)
{
	int pos;
	const char *j, *k;

	for (pos = 0; *s; ++s, ++pos) {
		for (j = s, k = t; *k && (*j == *k); ++j, ++k)
			;
		if (k > t && *k == '\0')
			return pos;
	}
	return -1;
}
