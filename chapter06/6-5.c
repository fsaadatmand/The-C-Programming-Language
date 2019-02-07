/*
 * Exercise 6-5. Write a function undef that will remove a name and a
 * definition from the table maintained by lookup and install.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {                         /* table entry: */
	struct nlist *next;                /* next entry in chain */
	char *name;                        /* defined name */
	char *defn;                        /* replacement text */
};

/* functions */
unsigned hash(char *);
char *strDup(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);

/* Globals */
static struct nlist *hashtab[HASHSIZE];    /* pointer table */

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

/* undef: remove (name, def) in hashtab */
int undef(char *s)
{
	struct nlist *np;

	if ((np = lookup(s)) != NULL) {
		np->next = NULL;               /* clear index/link in node */
		free((void *) np->name);       /* free array's memory */
		free((void *) np->defn);       /* free array's memory */
		free((void *) np);             /* free node memory */
		hashtab[hash(s)] = NULL;       /* clear index/link in hash table */
		return 1;                      /* success */
	}
	return -1;                         /* failure. No match found */
}

int main(void)
{
	struct nlist *p;
	int i;

	if ((p = install("YES", "1")) != NULL) 
		printf("YES is replaced by %s\n", p->defn); 

	if ((p = install("NO", "0")) != NULL) 
		printf("NO is replaced by %s\n", p->defn); 

	printf("\n");

	printf("Hash Table values:\n");
	i = 0;
	for (p = hashtab[i]; i < HASHSIZE; ++i) {
		p = hashtab[i];
		if (p != NULL)
			printf("%i  name: %s  defn: %s\n", i, p->name, p->defn);
	}

	printf("\n");

	undef("YES");

	printf("Hash Table values (after deletion):\n");
	i = 0;
	for (p = hashtab[i]; i < HASHSIZE; ++i) {
		p = hashtab[i];
		if (p != NULL)
			printf("%i  name: %s  defn: %s\n", i, p->name, p->defn);
	}
	return 0;
}
