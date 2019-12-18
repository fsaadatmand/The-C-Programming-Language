/*
 * Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
 * declaration.
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
void undcl(void);
int gettoken();

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[MAXLEN];         /* composed output string */
char state;               /* flag to propagate the current state of parsing */

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

/* needsParens: check if the next token is a parenthesis or a bracket */
int needsParens()
{
	void ungettokken(int);
	int nextType;

	nextType = gettoken(); /* peek ahead */
	state = FAIL; /* signal token push back */
	return nextType == PARENS || nextType == BRACKETS;
}

/* undcl: convert word descriptions to declarations */
void undcl(void)
{
	int type;
	char temp[MAXTOKEN];

	while ((type = gettoken()) != '\n')
		if (type == PARENS || type == BRACKETS)
			strcat(out, token);
		else if (type == '*') {
			sprintf(temp, needsParens() ? "(*%s)" : "*%s", out);
			strcpy(out, temp);
		} else if (type == NAME) {
			sprintf(temp, "%s %s", token, out);
			strcpy(out, temp);
		} else
			printf("invalid input at %s\n", token);
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

int main(void)
{
	while (gettoken() != EOF) {  /* first token on line */
		if (tokentype == '\n')  /* skip empty input lines */
			continue;
		strcpy(out, token); /* is the datatype */
		undcl();
		printf("%s\n", out);
	}
	return 0;
}
