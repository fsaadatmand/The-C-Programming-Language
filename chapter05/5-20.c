/*
 * Exercise 5-20. Expand dcl to handle declarations with function argument
 * types, qualifiers like const, and so on.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100
#define BUFSIZE     100

#define SKIP_BLANKS(c)  while (((c) = getch()) == ' ' || (c) == '\t')

enum { NAME, PARENS, BRACKETS };

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
char buf[BUFSIZE];                     /* buffer from ungetch */
int  bufp = 0;                         /* next free position in buf */
int  error;                            /* signals parsing failure */

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
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if (c == EOF)
		bufp = 0;                      /* clear buffer */

	if (bufp >= BUFSIZE && c != EOF)
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
	
	error = 0;
	if (tokentype == '(') {            /* ( dcl ) */
		dcl ();
		if (tokentype != ')') {
			printf("error: missing )\n");
			error = 1;
		}
	} else if (tokentype == NAME)      /* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		error = 1;
	}

	if (!error) {
		while ((type = gettoken()) == PARENS || type == BRACKETS)
			if (type == PARENS)
				strcat(out, " function returning");
			else {
			strcat(out, " array");
			strcat(out,  token);
			strcat(out, " of");
			}
	}
}

// parameter-type-list      loop that gets the tokens include ',' and stops at ')'
// parameter-declaration    checks tokens according to grammer
// declaration-specifiers   datatype?

/* convert declaration to words */
int main(void)               
{
	while (gettoken() != EOF) {        /* last token on line */
		strcpy(datatype, token);       /* is the datatype */
		out[0] = '\0';
		if (tokentype != '\n') {       /* skip empty input lines */
			dcl();
			if (tokentype != '\n')
				printf("syntax error\n");
			else if (!error)
				printf("%s: %s %s\n", name, out, datatype);
		}
	}
	return 0;
}
