/*
 * Exercise 5-17. Add a field-searching capability, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.)
 *
 * By Faisal Saadatmand
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES   5000      /* max #lines to be sorted */
#define MAXLEN     1000      /* max length of any input line */
#define ALLOCSIZE  10000     /* storage for memory[] */
#define NUMERIC    01        /* numeric sort */
#define REVERSE    02        /* reverse sort */
#define FOLD       04        /* case-insensitive sort */
#define DIRORDER   010       /* directory-order sort */
#define FIELD      020       /* field-search sort */

typedef int (*funcP)(void *, void*); /* type alias to simplify syntax
										see section 6.7 */
/* functions */
int getLine(char *, int);
int readlines(char *[], int);
void witelines(char *[], int, int);
char *alloc(int);
void qSort(void *[], int, int, funcP);
int strCmp(char *, char *);
int numcmp(char *, char *);
int foldCmp(char *, char *);
int dirCmp(char *, char *);
int expandArg(int, char **);
int fieldCmp(char *, char *);
funcP comparator(int);

/* globals */
static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */
static char option;               /* bit flag (1 byte in size) */
static long fieldpos;             /* beginning of the field position */

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}
	if (c == '\n') {
		*s++ = c;
		++len;
	}
	*s = '\0';
	return len;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		line[len - 1] = '\0';   /* delete newline character */
		strcpy(p, line);
		lineptr[nlines++] = p;
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int reverse)
{
	if (reverse)
		while (--nlines > 0) /* print lines in reverser order */
			printf("%s\n", lineptr[nlines]);
	else
		while (nlines-- > 0)
			printf("%s\n", *lineptr++);
}

/* alloc: return pointer to n characters */
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp < n)
		return 0; /* not enough room */
	allocp += n;
	return allocp - n; /* old p */
}

/* swap: swap the values of v[i] and v[j]. */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* qsort: sort v[left]...V[right] into increasing order */
void qSort(void *v[], int left, int right, funcP comp)
{
	int i, last;

	void swap(void *v[], int, int);

	if (left >= right)             /* do nothing if array contains */
		return;                    /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qSort(v, left, last - 1, comp);
	qSort(v, last + 1, right, comp);
}

/* strCmp: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strCmp(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
}

/* foldCmp: perform case-insensitive comparison between s and t */
int foldCmp(char *s, char *t)
{
	char str1[MAXLEN], str2[MAXLEN];
	int i;
	funcP fp;
	
	for (i = 0; *s; ++s) 
		str1[i++] = tolower(*s);
	str1[i] = '\0';
	for (i = 0; *t; ++t) 
		str2[i++] = tolower(*t);
	str2[i] = '\0';
	fp = comparator(option & DIRORDER); /* strCmp or dirCmp, exclude other options */
	return fp(str1, str2);
}

/* dirCmp: perform directory-order comparison--compare only letters, numbers
 * and blanks. */
int dirCmp(char *s, char *t)
{
	int i;
	char str1[MAXLEN], str2[MAXLEN];

	for (i = 0; *s != '\0'; ++s) 
		if (isalnum(*s) || isblank(*s))
			str1[i++] = *s;
	str1[i] = '\0';
	for (i = 0; *t != '\0'; ++t) 
		if (isalnum(*t) || isblank(*t))
			str2[i++] = *t;
	str2[i] = '\0';
	return strCmp(str1, str2);
}

/* fieldCmp: compare fields according to the field pos entered by user */
int fieldCmp(char *s, char *t)
{
	int i;
	funcP fp;

	for (i = 1; i < fieldpos && *s; ++s, ++i) {
		while (!isblank(*s) && *s)
			++s;
		while (isblank(*s)) /* skip any sequence of blanks */
			++s;
		--s; /* 'unread' 1 character */
	}
	for (i = 1; i < fieldpos && *t; ++t, ++i) {
		while (*t && !isblank(*t) && *t)
			++t;
		while (isblank(*t)) /* skip any sequence of blanks */
			++t;
		--t; /* 'unread' 1 character */
	}
	fp = comparator(option ^ FIELD); /* exclude fieldCmp */
	return fp(s, t);
}

/* comparator: return a function pointer to the compare function corresponding
 * to the input option(s). If no option was provided, i.e. the bit flag
 * 'option' was 0, return a function pointer to strCmp. */
funcP comparator(int option) 
{
	/*
	 * Because functions could use the comparator function to determine which
	 * operation to perform, the order of the checks is important. Moreover,
	 * when calling the comparator, the calling function must exclude itself
	 * and any preceding options in the checks order from the option bit flag.
	 */
	return (funcP) (option & FIELD ? fieldCmp : option & NUMERIC? numcmp :
			option & FOLD ? foldCmp : option & DIRORDER ? dirCmp : strCmp);
}

int expandArg(int count, char **list)
{
	char *prog, *endptr;
	int c, parseK;

	prog = *list; /* program name */
	option = parseK = 0;
	endptr = NULL;

	while (--count > 0 && **++list == '-') {
		while ((c = *++*list) && !parseK) {
			switch (c) {
			case ('n'):
				option |= NUMERIC;
				break;
			case ('r'):
				option |= REVERSE;
				break;
			case ('f'):
				option |= FOLD;
				break;
			case ('d'):
				option |= DIRORDER;
				break;
			case ('k'):
				option |= FIELD;
				parseK = 1;
				break;
			default:
				printf("%s: invalid option -- '%c'\n", prog, c);
				count = -1;
				break;
			}
		}
		if (parseK) {
			if (isdigit(c)) /* convert the rest of the string */
				fieldpos = strtol(*list, &endptr, 0);
			else if (c == '\0' && count > 1) { /* read and convert the next arg */
				fieldpos = strtol(*++list, &endptr, 0);
				--count;
			} else /* no number after -k */
				count = -1; /* break the loop */
			parseK = 0;
		}
	}
	if (option & NUMERIC && option & DIRORDER) {
		printf("%s: options '-dn' are incompatible\n", prog);
		count = -1;
	}
	if (option & FIELD && (!fieldpos || *endptr)) {
		printf("%s: option requires an argument -- 'k'\n", prog);
		count = -1;
	}
	if (count != 0) {
		printf("Usage: %s [-nr] [-fdr] [-k field]\n", prog);
		return -1; /* parsing failure */
	}
	return 0; /* parsing success or no argument was passed */
}

/* sort input lines */
int main(int argc, char *argv[])
{
	char *lineptr[MAXLINES];   /* pointers to text lines */
	int nlines;                /* number of input lines read */     

	if (expandArg(argc, argv) < 0)
		return 1;
	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		printf("input too big to sort\n");
		return 1;
	}
	qSort((void**) lineptr, 0, nlines - 1, comparator(option));
	writelines(lineptr, nlines, option & REVERSE);
	return 0;
}
