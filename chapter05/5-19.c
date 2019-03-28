/*
 * Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
 * declaration.
 * By Faisal Saadatmand
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100
#define BUFSIZE     100

#define SKIP_BLANKS(c)  while (((c) = getch()) == ' ' || (c) == '\t')

enum { NAME, PARENS, BRACKETS };

/* functions */
int  gettoken(void);
int  getch(void);
void ungetch(int);

/* globals */
char token[MAXTOKEN];                  /* last token string */
int  tokentype;                        /* type of last token */
char name[MAXTOKEN];                   /* identifier name */
char out[1000];
int  buf[BUFSIZE];                     /* buffer from ungetch */
int  bufp;                             /* next free position in buf */
int  pushedEOF;                        /* signals EOF has been pushed-back */

/* gettoekn: return next token */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	SKIP_BLANKS(c);

	if (c == '(') {
		SKIP_BLANKS(c);                /* allow spaces in parens */
		if (c == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p = getch()) != ']'; p++)
			if (*p == '\n')            /* error check: missing ']' */
				return *p;
		*++p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); p++)
			*p = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

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

/* undcl: convert word descriptions to declarations */
void undcl(void)
{
	int  type, is_dcl, error;
	char temp[1100];           /* increased size to avoid potential overflow */

	is_dcl = error = 0;
	strcpy(out, token);
	while ((type = gettoken()) != '\n') {
		if (type == PARENS || type == BRACKETS) {
			if (is_dcl) {          /* check if previous token is the start of dcl */
				sprintf(temp, "(%s)", out);
				strcpy(out, temp);
				is_dcl = 0;
				}
			strcat(out, token);
		} else if (type == '*') {
			sprintf(temp, "*%s", out);
			strcpy(out, temp);
			is_dcl = 1;
		} else if (type == NAME) {
			sprintf(temp, "%s %s", token, out);
			strcpy(out, temp);
		} else {
			printf("invalid input at %s\n", token);
			error = 1;
		}
	}
	if (!error)
		printf("%s\n", out);
}

int main(void)               
{
	while (gettoken() != EOF)
		if (tokentype != '\n')         /* skip empty input lines */
			undcl();
	return 0;
}
