/*
 * Exercise 5-18. Make dcl recover from input error.
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE   100
#define MAXLEN    1000
#define MAXTOKEN  100

enum { NAME, PARENS, BRACKETS };
enum { GOOD, FAIL };

/* functions */
void dcl(void);
void dirdcl(void);
int gettoken();
void errmsg(const char *);

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[MAXLEN];         /* composed output string */
char state;               /* flag to propagate the current state of parsing */

/* dcl: parse a declarator */
void dcl(void)
{
	int ns; /* number of asterisks */

	for (ns = 0; gettoken() == '*'; ++ns) /* count *'s */
		;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(') {         /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			errmsg("error: missing )\n");
	} else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else 
		errmsg("error: expected name of (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* errmsg: print error message, set state flag to FAIL */
void errmsg(const char *msg)
{
	printf("%s", msg);
	state = FAIL; /* propagate state of parsing to allow for error recovery */
}

/* gettoken: return next token */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	if (state == FAIL) {
		state = GOOD;
		return tokentype; /* push back the previous token */
	}
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		ungetch(c);
		return tokentype = '(';
	} 
	if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	return tokentype = c;
}

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

/* convert declaration to words */
int main(void)
{
	while (gettoken() != EOF) {  /* first token on line */
		if (tokentype == '\n')   /* skip empty lines */
			continue;
		strcpy(datatype, token); /* is the datatype */
		out[0] = '\0';
		dcl();                   /* parse rest of line */
		if (tokentype != '\n')
			printf("%s", "syntax error\n");
		else if (state == GOOD)
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
