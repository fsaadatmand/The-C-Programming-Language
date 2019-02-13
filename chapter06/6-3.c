/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the," "and," and so on.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS   (sizeof noisetab / sizeof noisetab[0])

struct tnode {
	char *word;
	struct list *line;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct list {
	int number;
	struct list *next;
};

struct key {
	char *word;
	int  count;
};

struct key noisetab[] = {
	{ "a", 0 },
	{ "and", 0 },
	{ "is", 0 },
	{ "of", 0},
	{ "on", 0},
	{ "the", 0 },
	{ "to", 0 },
	{ "was", 0},
	{ "were", 0},
	{ "with", 0},
};

/* functions */
int    getword(char *, int, int *);
struct tnode *talloc(void);            /* allocate memory to new tree node */
char   *strDup(char *);                /* copy string into safe place */
struct tnode *addtree(struct tnode *, char *, int);
void   treeprint(struct tnode *);
void   printList(struct list *);
struct key *binsearch(char *, struct key *, int);

/* globals */
char   buf[BUFSIZE];                   /* buffer from ungetch */
int    bufp = 0;                       /* next free position in buf */

/* getword: get next word or character from input */
int getword(char *word, int lim, int *ln)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		if (c == '\n')
			(*ln)++;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/*strDup: make a duplicate of s */
char *strDup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* addList: add a node with ln, at or before p */
struct list *addlist(struct list *p, int ln)
{
	if (p == NULL) {
		p = (struct list *) malloc(sizeof(struct list));
		p->number = ln;
		p->next = NULL;
	} else if (p->number != ln)        /* skip multi-occurrence on same line */  
		p->next = addlist(p->next, ln); 
	
	return p;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int ln)
{
	int cond;
	struct list *first = NULL;

	if (p == NULL) {                   /* a new word has arrived */
		p = talloc();                  /* make a new node */
		p->word = strDup(w);           /* copy data to it */
		p->count = 1;
		p->line = addlist(first, ln);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;                    /* repeated word */
		p->line = addlist(p->line, ln);
	} else if (cond < 0)               /* less than into left subtree */
		p->left = addtree(p->left, w, ln);
	else  
		p->right = addtree(p->right, w, ln);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s ", p->count, p->word);
		printList(p->line);
		printf("\n");
		treeprint(p->right);
	}
}

/* printList: preorder print of list p */
void printList(struct list *p)
{
	if (p != NULL) {
		printf("%d ", p->number);
		printList(p->next);
	}
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

int main(void)
{
	struct tnode *root;                /* root node */
	struct key *p;                     /* currently searched word */
	char word[MAXWORD];                /* currently read word */
	int lineNumb;                      /* currently searched line */
	int *pLineNumb;                    /* pointer to change value of lineNumb */

	root = NULL;
	pLineNumb = &lineNumb;
	*pLineNumb = 1;                    /* start at line 1 */

	while (getword(word, MAXWORD, pLineNumb) != EOF) {
		p = binsearch(word, noisetab, NKEYS);    /* skip noise words */
		if (isalpha(word[0]) && p == NULL)
			root = addtree(root, word, lineNumb);
	}
	treeprint(root);
	return 0;
}
