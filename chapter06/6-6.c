/*
 * Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, base on the routines of this
 * section. You may also find getch and ungetch helpful.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define MAXLEN  5000
#define BUFSIZE 100
#define NSYMBOLS (sizeof symbol / sizeof symbol[0])

struct key {
	char *word;
	int count;
};

struct nlist {                          /* table entry: */
	struct nlist *next;                 /* next entry in chain */
	char *name;                         /* defined name */
	char *defn;                         /* replacement text */ 
};

/* globals */
char   buf[BUFSIZE];                    /* buffer from ungetch */
int    bufp = 0;                        /* next free position in buf */
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct key symbol[] = {                 /* array is sorted for binary search */
	{ "\"", 0 },
	{ "#", 0 },
	{ "*", 0 },
	{ "/", 0 },
	{ "\\", 0 },
	{ "_", 0 },
};

/* functions */
struct key *binsearch(char *, struct key *, int);
int getword(char *, int);
int getLine(char *, int);
char *strDup(char *);
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

/* binsearch: find word in tab[0]...tab[n - 1] */
struct key *binsearch(char *word, struct key *tab, int n)
{
	int cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n];
	struct key *mid;

	while (low < high) {
		mid = low + (high - low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
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

/* getword: get next word or character from input: C program specific (modified
 * for define preprocessor control line) */
int getword(char *word, int lim)
{
	int   c, getch(void);
	void  ungetch(int);
	char  *w = word;
	struct key *p; 

	while (isspace(c = getch()))
		;
	
	if (c != EOF) {
		*w++ = c;
		*w = '\0';
	} else
		return c;

	if (!isalpha(c) && (p = binsearch(word, symbol, NSYMBOLS)) == NULL)
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
	case '/':                          /* skip words inside C comments */
		if ((c = getch()) == '*') {
			while ((c = getch()))
				if	(c == '*' && (c = getch()) == '/')
					break; 
				else if (c == EOF)
					return c;
		} else                         /* don't skip pointer variables */
			ungetch(c);
		break;
	default:
		if (c == '#') {
			while (isspace(c = getch()))
				;
			*w++ = c;
		}

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

/* getLine: get line into s, return length of s -- modified to skip blanks at
 * the beginning of the line and not to insert a newline character at the end.
 * */
int getLine(char *s, int lim)
{
	int c, len;

	while (isspace(c = getch()))
		;
	*s++ = c;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}

	*s = '\0';
	return len;
}

/*strDup: make a duplicate of s. Error checking is handled by the caller */
char *strDup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + (31 * hashval);
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;                 /* found */
	return NULL;
}

/* install: put (name, def) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strDup(name)) == NULL)
			return NULL;               /* no (heap) memory */
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else                             /* already there */
		free((void *) np->defn);       /* free previous definition */

	np->defn = strDup(defn);           /* copy definition */

	if (np->defn == NULL)
		return NULL;
	return np;
}

/* simple define processor (no arguments) */
int main (void)
{
//	struct nlist *p;
	char word[MAXWORD];
	char defn[MAXLEN];
	char *name, *keyword = "#define";
	int ctrline, len, i;

	name = word;                       /* unnecessary. Added for clarity */

	ctrline = 0;
	while (getword(word, MAXWORD) != EOF)
		if (word[0] == '#' && !ctrline) {
			if (strcmp(word, keyword) == 0)
				ctrline = 1;           /* found processor control line */
		} else if (ctrline) {          /*  parse name and definition */
			len = getLine(defn, MAXLEN);
			install(name, defn);
			ctrline = 0;
		}

	/* print table */
	printf("Hash Table Values:\n");
	for (i = 0; i < HASHSIZE; i++)
		if (hashtab[i] != NULL)
			printf("%i  name: %s  defn: %s\n",
					i, hashtab[i]->name, hashtab[i]->defn);
	return 0;
}
