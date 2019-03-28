/*
 * Exercise 5-18. Make dcl recover from input error.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN        100
#define BUFSIZE         100
#define EMPTY_LINE      (tokentype == '\n')
#define RECOVER(c)       while (((c) = getch()) != '\n')
#define SKIP_BLANKS(c)  while (((c) = getch()) == ' ' || (c) == '\t')

enum { NAME, PARENS, BRACKETS, ERROR };

/* functions */
int  gettoken(void);
void dcl(void);
void dirdcl(void);
int  getch(void);
void ungetch(int);

/* globals */
char token[MAXTOKEN];                  /* last token string */
int  tokentype;                        /* type of last token */
char name[MAXTOKEN];                   /* identifier name */
char datatype[MAXTOKEN];               /* data type = char, int, etc. */
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

/* dcl: parse a declarator */
void dcl (void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )  /*count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(') {            /* ( dcl ) */
		dcl ();
		if (tokentype != ')') {
			printf("error: missing )\n");
			tokentype = ERROR;
		}
	} else if (tokentype == NAME) {    /* variable name */
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
		tokentype = ERROR;
	}

	if (tokentype == ERROR)
		return;

	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
		strcat(out, " array");
		strcat(out, token);
		strcat(out, " of");
	}
}

/* convert declaration to words */
int main(void)               
{
	int c;

	while (gettoken() != EOF) {        /* last token on line */
		strcpy(datatype, token);       /* is the datatype */
		out[0] = '\0';
		if (EMPTY_LINE)
			continue;                  /* skip empty input lines */
		dcl();
		if (tokentype != '\n') {
			printf("syntax error\n");
//			RECOVER(c);
//			ungetch(c);
		} else
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
