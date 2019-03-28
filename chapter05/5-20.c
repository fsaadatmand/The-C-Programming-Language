/*
 * Exercise 5-20. Expand dcl to handle declarations with function argument
 * types, qualifiers like const, and so on.
 *
 * Grammer (simplified):
 *  declaration:
 *   dcl -> *'s opt dirdcl
 *   dirdcl -> name | (dcl) | dirtdcl() | dirdcl(paramlist) | dirdcl[size opt]
 *
 *  function parameter's declaration:
 *   paramlist -> paramdecl | paramlist , paramdecl
 *   paramdecl -> declaration-specifiers dcl
 *
 * TODO: error checking is still finicky, e.g.: "int f(char f()" will not recover; add
 * type-qualifiers support.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN        100
#define BUFSIZE         100
#define EMPTY_LINE      (tokentype == '\n')
#define RECOVER         while (tokentype != EOF && gettoken() != '\n')    
#define SKIP_BLANKS(c)  while (((c) = getch()) == ' ' || (c) == '\t')

enum { NAME, PARENS, BRACKETS, ERROR };

/* functions */
int  gettoken(void);
void dcl(void);
void dirdcl(void);
int  getch(void);
void ungetch(int);
void paramList(void);
void paramdcl(void);

/* globals */
char token[MAXTOKEN];                  /* last token string */
int  tokentype;                        /* type of last token */
char name[MAXTOKEN];                   /* identifier name */
char datatype[MAXTOKEN];               /* data type = char, int, etc. */
char paramDataType[1000];              /* parameter data type */
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
			if (*p == '\n')            /* error check for missing ']' */
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

/* ungerch: push character back on input */
void ungetch(int c)
{
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
			tokentype = ERROR;
			printf("error: missing )\n");
		}
	} else if (tokentype == NAME) {      /* variable name */
		strcpy(name, token);
	} else { 
		tokentype = ERROR;
		printf("error: expected name or (dcl)\n");
	}

	if (tokentype == ERROR)
		return;

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function accepts");
			paramList();
			strcat(out, " returning");
			if (tokentype == ERROR)
				return;
		} else {
		strcat(out, " array");
		strcat(out,  token);
		strcat(out, " of");
	}
}

void paramdcl(void)
{
	char prevName[MAXTOKEN];

	strcpy(prevName, name);             /* save main function's name */
	dcl();                              /* note: dcl will skip current token */
	strcpy(name, prevName);             /* restore mian function's name */
}

void paramList(void)
{
	do {
		if (gettoken() == '\n') {
			printf("error: parameters syntax\n");
			tokentype = ERROR;
			return;
		}

		if (tokentype == NAME) {
			sprintf(paramDataType, " %s", token);
			paramdcl();
		}
		if (tokentype == ERROR)
			return;
		else if (tokentype == ',' || tokentype == ')') {
			strcat(out, paramDataType);
			if (tokentype == ',')
				strcat(out, " and" );
		}
	} while (tokentype != ')'); 
}

/* convert declaration to words */
int main(void)               
{
	while (gettoken() != EOF) {        /* last token on line */
		strcpy(datatype, token);       /* is the datatype */
		out[0] = '\0';
		if (EMPTY_LINE)
			continue;                  /* skip empty input lines */
		dcl();
		if (tokentype != '\n' || tokentype == ERROR)
			printf("syntax error\n");
		else
			printf("%s: %s %s\n", name, out, datatype);
}
	return 0;
}
