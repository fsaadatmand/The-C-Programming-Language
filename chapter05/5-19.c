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

enum { NAME, PARENS, BRACKETS };

/* functions */
int  gettoken(void);
int  getch(void) ;
void ungetch(int c);

/* Globals */
char token[MAXTOKEN];                  /* last token string */
int  tokentype;                        /* type of last token */
char name[MAXTOKEN];                   /* indentifier name */
char out[1000];
char buf[BUFSIZE];                     /* buffer from ungetch */
int  bufp = 0;                         /* next free position in buf */

/* gettoekn: return next token */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else return tokentype = c;
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
		bufp = 0;            /* clear buffer */

	if (bufp >= BUFSIZE && c != EOF)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* undcl: convert word descriptions to declarations */
int main(void)               
{
	int  type, prevType;
	char temp[MAXTOKEN];
	int  error;

	while (gettoken() != EOF) {
		error = 0;
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {
			if (type == PARENS || type == BRACKETS) {
				if (prevType == '*') {          /* check for precedence */
					sprintf(temp, "(%s)", out); /* add parentheses */
					strcpy(out, temp);
				}
				strcat(out, token);
			} else if (type == '*') {
				sprintf(temp, "*%s", out);     /* no general redundant parens */
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);
				error = 1;
			}
			prevType = type;
		}
		if (!error)
			puts(out);
	}
	return 0;
}
