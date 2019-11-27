/*
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES   5000      /* max #lines to be sorted */
#define MAXLEN     1000      /* max length of any input line */
#define ALLOCSIZE  100000    /* storage for alloc */
#define NUMERIC    01        /* numeric sort */
#define REVERSE    02        /* reverse sort */

typedef int (*funcP)(void *, void*); /* type alias to simplify syntax
										see section 6.7 */

/* functions */
int getLine(char *, int);
int readlines(char *[], int);
void witelines(char *[], int);
char *alloc(int);
void qSort(void *[], int, int, funcP);
int numcmp(char *, char *);
funcP comperator(int);

/* globals */
static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */
static char option;               /* bit flag (1 byte in size) */

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

/* strCmp: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strCmp(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
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
	return (funcP) (option & NUMERIC ? numcmp : strCmp);
}

/* sort input lines */
int main(int argc, char *argv[])
{
	char *lineptr[MAXLINES];  /* pointers to text lines */
	int nlines;               /* number of input lines read */     

	/* Note: no input error checking */
	option = 0;
	while (--argc > 0) {
		++argv;
		if (!strCmp(argv[0], "-n"))
			option |= NUMERIC;
		if (!strCmp(argv[0], "-r"))
			option |= REVERSE;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		printf("input too big to sort\n");
		return 1;
	}
	qSort((void**) lineptr, 0, nlines - 1, comparator(option));
	writelines(lineptr, nlines, option & REVERSE);
	return 0;
}
