/*
 * Exercise 6-1. Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better
 * version.
 * Note: getword underscore, string constant, comments and preprocessor control
 * line could be improved.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])
#define NSYMBOLS (sizeof symbol / sizeof symbol[0])
/* or */
/* #define NKEYS (sizeof keytab / sizeof(struct key)) */
#define BUFSIZE     100

/* globals */
int    buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */

struct key {
	char *word;
	int count;
};

struct key keytab[] = {
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "do", 0 },
	{ "double", 0 },
	{ "else", 0 },
	{ "enum", 0 },
	{ "extern", 0 },
	{ "float", 0 },
	{ "goto", 0 },
	{ "if", 0 },
	{ "int", 0 },
	{ "long", 0 },
	{ "register", 0 },
	{ "return", 0 },
	{ "short", 0 },
	{ "signed", 0 },
	{ "sizeof", 0 },
	{ "static", 0 },
	{ "struct", 0 },
	{ "switch", 0 },
	{ "typeof", 0 },
	{ "union", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },
};

struct key symbol[] = {                /* array is sorted for binary search */
	{ "\"", 0 },
	{ "#", 0 },
	{ "*", 0 },
	{ "/", 0 },
	{ "\\", 0 },
	{ "_", 0 },
};

/* functions */
int  getword(char *, int);
int  binsearch(char *, struct key *, int);

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getch(void)              /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)          /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int   c, n = -1, getch(void);
	void  ungetch(int);
	char  *w = word;

	while (isspace(c = getch()))
		;
	
	if (c != EOF) {
		*w++ = c;
		*w = '\0';
	} else
		return c;

	if (!isalpha(c) && (n = binsearch(word , symbol, NSYMBOLS)) < 0)
		return c;

	switch (c) {
	case '\\':                          /* handle escape sequences */
		c = getch();
		break;
	case '\"':                          /* skip words inside string constant */
		while ((c = getch()) != '\"')
			if (c == EOF)
				return c;
		break;
	case '#':                          /* skip preprocessor control lines */
		while ((c = getch()) != '\n')
			;
		ungetch(c);
		break;
	case '/':                          /* skip words inside C comments */
		if ((c = getch()) == '*') {
			while ((c = getch()))
				if	(c == '*' && (c = getch()) == '/')
					break; 
				else if (c == EOF)
					return c;
		}
		break;
	default:
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
		break;
	}

	*w = '\0';
	return word[0];
}

/* count C keywords */
int main(void)
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < (int) NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}
