/*
 * Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful.
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD  100
#define MAXLEN   5000
#define BUFSIZE  100

struct nlist {                          /* table entry: */
	struct nlist *next;                 /* next entry in chain */
	char *name;                         /* defined name */
	char *defn;                         /* replacement text */ 
};

/* globals */
int buf[BUFSIZE];                       /* buffer from ungetch */
int bufp = 0;                           /* next free position in buf */
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* functions */
int getword(char *, int);
int getdef(char *, int);
char *strDup(char *);
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void printtab(struct nlist *[], int);
void freetable(struct nlist *[], int);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; ++w)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'') /* skip character constants */
		while ((c = getch()) != '\'')
			;
	else if (c == '\"')  { /* skip string constants */
		while ((c = getch()) != '\"')
			if (c == '\\')
				getch();
	} else if (c == '/' && (c = getch()) == '*') /* skip comments */
		while ((c = getch()) != EOF)
			if (c == '*' && (c = getch()) == '/')
				break;
	*w ='\0';
	return c;
}

/* get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getdef: copy the rest of the line int s, return length of s. This is a
 * modified version of getLine, which skips leading blanks andd does not insert
 * a newline character at the end. */
int getdef(char *s, int lim)
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

	p = malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p)
		strcpy(p, s);
	return p;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s; ++s)
		hashval = *s + (31 * hashval);
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np; np = np->next)
		if (!strcmp(s, np->name))
			return np;                 /* found */
	return NULL;
}

/* install: put (name, def) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if (!(np = lookup(name))) {        /* not found */
		np = malloc(sizeof(*np));
		if (!np || !(np->name = strDup(name)))
			return NULL;               /* no (heap) memory */
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else                             /* already there */
		free((void *) np->defn);       /* free previous definition */
	if (!(np->defn = strDup(defn)))    /* copy definition */
		return NULL;
	return np;
}
/* printtab: prints content of hashtable, linear scan */
void printtab(struct nlist *node[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
		if (node[i])
			printf("%i  name: %s  defn: %s\n", i, node[i]->name, node[i]->defn);
}

/* freetable: free table's (and its content's) allocated memory from heap */
void freetable(struct nlist *node[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
		if (node[i]) {
			free(node[i]->name);
			free(node[i]->defn);
			free(node[i]);
		}
}

int main (void)
{
	char word[MAXWORD];
	char defn[MAXLEN];
	const char *keyword = "#define";

	while (getword(word, MAXWORD) != EOF)
		if (word[0] == '#' && !strcmp(word, keyword)) {  /* found #define */
			getword(word, MAXLEN);   /* get the name */
			getdef(defn, MAXLEN);    /* parse definition */
			install(word, defn);
		}
	printf("Hash Table Values:\n");
	printtab(hashtab, HASHSIZE);
	freetable(hashtab, HASHSIZE);      /* clean up */
	return 0;
}
