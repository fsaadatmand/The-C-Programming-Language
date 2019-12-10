/*
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence. Precede each word by its count.
 *
 * By Faisal Saadatmand
 */

/* NOTE: I included a definition for sorttree and copytree for academic
 * purposes. They are not used in the code */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

/* types */
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

/* functions */
int getword(char *, int);
struct tnode *talloc(void);        /* allocate memory to new tree node */
char *strDup(char *);              /* copy string into safe place */
struct tnode *addtree(struct tnode *, char *);
void printtree(struct tnode *);
void freetree(struct tnode *);
struct tnode *sorttree(struct tnode *, struct tnode *); /* optional */

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (!p) {                          /* a new word has arrived */
		p = talloc();                  /* make a new node */
		p->word = strDup(w);           /* copy data to it */
		p->count = 1;
		p->left = p->right = NULL;
	} else if (!(cond = strcmp(w, p->word)))
		++p->count;                    /* repeated word */
	else if (cond < 0)                 /* less than into left subtree */
		p->left = addtree(p->left, w);
	else  
		p->right = addtree(p->right, w);
	return p;
}

/* print: in-order print of tree p - decreasing order version */
void printtree(struct tnode *p)
{
	if (p) {
		printtree(p->right);
		printf("%4d %s\n", p->count, p->word);
		printtree(p->left);
	}
}

/* copyTree: copy nodes in root into p according to frequency of occurrence. */
struct tnode *copyTree(struct tnode *p, struct tnode *root)
{
	if (!p) {
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

/* sorttree: performs inorder traversal on root and creates a BST p according
 * to frequency of occurrence */
struct tnode *sorttree(struct tnode *p, struct tnode *root)
{
	struct tnode *copyTree(struct tnode *, struct tnode *);

	if (root) {
		p = sorttree(p, root->left);
		p = copyTree(p, root);
		p = sorttree(p, root->right);
	}
	return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return malloc(sizeof(struct tnode));
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

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isblank(c = getch()))
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

int main(void)
{
	struct tnode *root;                /* root node */
	char word[MAXWORD];                /* currently read word */

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = (addtree(root, word)); /* build tree */
	printtree(root);
	freetree(root);
	root = NULL;
	return 0;
}
