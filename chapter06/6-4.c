/*
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence. Precede each word by its count.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

/* functions */
int getword(char *, int);
struct tnode *talloc(void);            /* alocate memory to new tree node */
char   *strDup(char *);                /* copy string into safe place */
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *copyTree(struct tnode *, struct tnode *);
struct tnode *sortTree(struct tnode *, struct tnode *);

/* globals */
char   buf[BUFSIZE];                   /* buffer from ungetch */
int    bufp = 0;                       /* next free position in buf */

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
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
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

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {                   /* a new word has arrived */
		p = talloc();                  /* make a new node */
		p->word = strDup(w);           /* copy data to it */
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;                    /* repeated word */
	else if (cond < 0)                 /* less thant into left subtree */
		p->left = addtree(p->left, w);
	else  
		p->right = addtree(p->right, w);
	return p;
}

/* print: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->right);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->left);
	}
}

/* copyTree: copy nodes in root into p according to frequency of occurrence. */
struct tnode *copyTree(struct tnode *p, struct tnode *root)
{
	if (p == NULL) {
		p = talloc();
		p->word = strDup(root->word);
		p->count = root->count;
		p->left = p->right = NULL;
	} else if (root->count <= p->count)
		p->left = copyTree(p->left, root);
	else
		p->right = copyTree(p->right, root);
	return p;
}

/* sortTree: performs inorder traversal on root and creates a BST p according
 * to frequencey of occurence */
struct tnode *sortTree(struct tnode *p, struct tnode *root)
{
	if (root != NULL) {
		sortTree(p, root->left);
		p = copyTree(p, root);
		sortTree(p, root->right);
	}
	return p;
}

int main(void)
{
	struct tnode *root;                /* root node */
	struct tnode *sRoot;               /* root node to sorted tree */
	char word[MAXWORD];                /* currently read word */

	root = sRoot =  NULL;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = (addtree(root, word));
	sRoot = sortTree(sRoot, root);
	treeprint(sRoot);
	return 0;
}
