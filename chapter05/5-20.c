/*
 * Exercise 5-20. Expand dcl to handle declarations with function argument
 * types, qualifiers like const, and so on.
 *
 * By Faisal Saadatmand
 */

/*
 * Expanded grammar to: (refer to Appendix A, sections 8, 8.2, 8.5 and 8.6.3)
 *
 *   declaration:
 *   	dclspc dcl
 *
 *   dclspc:
 *   	typespc dclspc
 *   	typespc dclspc_opt
 *
 *   dcl:
 *   	optional *'s dirdcl
 *
 *   dirdcl:
 *   	name
 *   	( dcl )
 *   	dirdcl( paramdcl_opt )
 *   	dirdcl[ size_opt ]
 *
 *   paramdcl:
 *   	paramdcl , dclspc dcl
 *
 *
 * NOTE: for simplicity's sake, typespc supports only char, double, float, int
 * and void; qualspc supports const and volatile. There is no support for
 * pointer qualifiers.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE   100
#define MAXLEN    1000
#define MAXTOKEN  100

#define SIZE(a)   sizeof((a)) / sizeof((a)[0])

enum { NAME, PARENS, BRACKETS };
enum { GOOD, FAIL };

/* functions */
void dcl(void);
void dirdcl(void);
int gettoken();
void errmsg(const char *);
void dclspc(char *);
int typespc(void);
int typeqaul(void);
void paramdcl(void);

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[MAXLEN];         /* composed output string */
char state;               /* flag to propagate the current state of parsing */
int paramtype;            /* signal that type is a parameter type */

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
	} else if (tokentype == NAME) { /* variable name */
		if (!name[0])               /* skip if name exists */
			strcpy(name, token);
	} else {
		if (paramtype)
			state = FAIL; /* push back tokentype without printing error msg */
		else
			errmsg("error: expected name or (dcl)\n");
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function expecting");;
			paramdcl();
			strcat(out, " and returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* paramdcl: parse parameter-declaration */
void paramdcl(void)
{  
	char temp[MAXTOKEN];

	do {
		temp[0] = '\0'; /* clear previous parameter type */
		gettoken();
		dclspc(temp);
		paramtype = 1; /* allow type-specifier without names */
		dcl();
		paramtype = 0;
		if (tokentype == ',')
			strcat(temp, ",");
		strcat(out, " ");
		strcat(out, temp);
	} while (tokentype == ',');
	if (tokentype != ')')
		errmsg("missing ) in parameter declaration\n");
}

/* decl-spc: parse a declarations-specifier */
void dclspc(char *type)
{
	int count;

	for (count = 0; tokentype == NAME && (typespc() || typeqaul()); ++count) {
		if (count) /* qualifier added? */
			strcat(type, " ");
		strcat(type, token); /* is the datatype */
		gettoken();
	}
	state = FAIL; /* push back previous token */
}

/* typespc: return 1 if token is a type-specifier, otherwise return 0 */
int typespc(void)
{
	int isequal(const void *, const void *), combination_chk();
	static const char *typetab[] = { "char", "double", "float", "int", "void" };

	if (!bsearch(&token, typetab, SIZE(typetab), sizeof(char *), isequal))
		return 0; /* not a specifier */
	return 1;
}

/* typequal: return 1 if token is type-qualifier, otherwise return 0 */
int typeqaul(void)
{
	int isequal(const void *, const void *), combination_chk();
	static const char *qualtab[] = { "const", "volatile" };

	if (!bsearch(&token, qualtab, SIZE(qualtab), sizeof(char *), isequal))
		return 0;
	return 1;
}

/* isequal: comparator function: return 0 if the content of s is equal to t,
 * otherwise return a non-zero value */
int isequal(const void *s, const void *t)
{
	return strcmp((char *) s, *(char **) t);
}

/* errmsg: print error message, set state flag to FAIL */
void errmsg(const char *msg)
{
	printf("%s", msg);
	state = FAIL;
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

int main(void)
{
	while (gettoken() != EOF) {  /* first token on line */
		if (tokentype == '\n')   /* skip empty lines */
			continue;
		datatype[0] = '\0';
		dclspc(datatype);        /* parse data type */
		name[0] = out[0] = '\0';
		dcl();                   /* parse rest of line */
		if (tokentype != '\n')
			printf("%s", "syntax error\n");
		else if (state == GOOD)
			printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
