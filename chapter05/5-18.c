/* Exercise 5-18. Make dcl recover from input error. By Faisal Saadatmand */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100
#define BUFSIZE     100

enum { NAME, PARENS, BRACKETS };

/* functions */
int  gettoken(void);
int dcl(void);
int dirdcl(void);

/* Globals */
char token[MAXTOKEN];                  /* last token string */
int  tokentype;                        /* type of last token */
char name[MAXTOKEN];                   /* indentifier name */
char datatype[MAXTOKEN];               /* data type = char, int, etc. */
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

/* dcl: parse a declarator */
int dcl (void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )  /*count *'s */
		ns++;
	if (dirdcl() >= 0) {
		while (ns-- > 0)
			strcat(out, " pointer to");
	return 0;
	} else
		return -1;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void)
{
	int type;
	
	if (tokentype == '(') {            /* ( dcl ) */
		if (dcl () < 0 || tokentype != ')') {
//		if (tokentype != ')') {
			printf("error: missing )\n");
			return -1;
		}
	} else if (tokentype == NAME)      /* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		return -1;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
		strcat(out, " array");
		strcat(out,  token);
		strcat(out, " of");
		}
	return 0;
}

/* convert declaration to words */
int main(void)               
{
	while (gettoken() != EOF) {        /* last token on line */
		strcpy(datatype, token);       /* is the datatype */
		out[0] = '\0';
		if (dcl() < 0 || tokentype != '\n') {                        /* parse rest of line */
			printf("syntax error\n");
			/* error recovery: reset pointers */
			name[0] = out[0] = datatype[0] = token[0] = buf[0] = '\0';
			bufp = tokentype = 0;
		} else
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
