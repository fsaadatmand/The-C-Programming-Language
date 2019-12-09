/* 
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group variable names that are identical in the first
 * 6 characters, but different somewhere thereafter. Don't count words within
 * string and comments. Make 6 a parameter that can be set from the command
 * line.
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>                   /* for malloc && atoi */
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (int) (sizeof keytab / sizeof keytab[0])

/* types */
struct tnode {                     /* the tree node: */
	char *word;                    /* points to the text */
	int match;                     /* number of occurrences */
	struct tnode *left;            /* left child */
	struct tnode *right;           /* right child */
};

struct key {
	char *word;
	int count;
};

/* functions */
int getword(char *, int);
struct key *binsearch(char *, struct key *, int); 
struct tnode *addtree(struct tnode *, char *, size_t n);
struct tnode *talloc(void);        /* alocate memory to new tree node */
char *strDup(char *);              /* copy string into safe place */
void checkmatch(char *, struct tnode *, size_t, int *);
void printtree(struct tnode *);
void freetree(struct tnode *);

/* globals */
int buf[BUFSIZE];                   /* buffer from ungetch */
int bufp = 0;                       /* next free position in buf */

struct key keytab[] ={
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
	{ "for", 0 },
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

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, size_t n)
{
	int cond;
	static int found;

	if (!p) {                 /* a new word has arrived */
		p = talloc();         /* make a new node */
		p->word = strDup(w);  /* copy data to it */
		p->match = *(&found); /* p->match = value pointed to by &found */
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) < 0) { /* less than ? */
		checkmatch(w, p, n, &found);
		p->left = addtree(p->left, w, n); /* go left */
	} else if (cond > 0) {     /* greater than */
		checkmatch(w, p, n, &found);
		p->right = addtree(p->right, w, n); /* go right */
	}
	found = 0; /* reset */
	return p;
}

/* checkmatch: set current node's flag variable and the found variable to 1, if
 * w matches a word in the tree */
void checkmatch(char *w, struct tnode *p, size_t n, int *found)
{
	if (!strncmp(w, p->word, n)) /* is w a match? */
		p->match = *found = 1; /* mark the current and the next nodes */
}

/* printree: in-order print of tree p */
void printree(struct tnode *p)
{
	if (!p) /* exist condition */
		return;
	printree(p->left);
	if (p->match)
		printf(" %s\n", p->word);
	printree(p->right);
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return malloc(sizeof(struct tnode));
}

/* freetree: free allocated heap memory of node tree */
void freetree(struct tnode *node)
{
	if (!node)
		return;
	freetree(node->left);
	freetree(node->right);
	free(node->word);
	free(node);
}

/*strDup: make a duplicate of s */
char *strDup(char *s)
{
	char *p;

	p = malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p)
		strcpy(p, s);
	return p;
}

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

int main(int argc, char *argv[])
{
	struct tnode *root;             /* root node */
	char word[MAXWORD];             /* currently read word */
	size_t nChar;                   /* number of characters to match */

	nChar = (--argc == 1) ? atoi(*++argv) : 6; /* Note: no input error check */
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if ((isalpha(word[0]) || word[0] == '_') && strlen(word) >= nChar &&
				!binsearch(word, keytab, NKEYS)) /* skip reserved words */
			root = addtree(root, word, nChar);                  
	printree(root);
	/* clean up */
	freetree(root);
	root = NULL;
	return 0;
}
