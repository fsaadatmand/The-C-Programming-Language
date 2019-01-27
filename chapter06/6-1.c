/*
 * Exercise 6-1. Our version of getword does not properly handle underscores,
 * sting constants, comments, or preprocessor control lines. Write a better
 * version.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])
/* or */
/* #define NKEYS (sizeof keytab / sizeof(struct key)) */
#define BUFSIZE     100

char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */

struct key {
	char *word;
	int count;
} keytab[] ={
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "define" , 0 },
	/* ... */
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },
};

struct key notation[] = {
	{ "_", 0 },
	{ "\"", 0 },
	{ "/", 0 },
	{ "*", 0 },
	{ "#", 0 },
};

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
	int   c, getch(void);
	void  ungetch(int);
	char  *w = word;

	while (isspace(c = getch()))
		;

	if (c == '\"')           /* skip sting constants */
		while ((c = getch()) != EOF && c != '\"')
			;

	if (c != EOF)
		*w++ = c;

	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
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

