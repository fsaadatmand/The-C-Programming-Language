/*
 * Exercise 5-15. Add the option -f to fold upper and lower case together, so
 * that case distinctions are not made during sorting; for example, a and A
 * compare equal.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES   5000      /* max #lines to be sorted */
#define MAXLEN     1000      /* max length of any input line */
#define ALLOCSIZE 100000     /* storage for alloc */

/* functions */
int  getLine(char *, int);
int  readlines(char *[], int);
void witelines(char *[], int);
char *alloc(int);
void qSort(void *[], int, int,
		int (*)(void *, void *));
int  numcmp(char *, char *);
int  strCmp(char *, char *);
int  reverse(char *, char *);
int  fstrCmp(char *, char *);

/* globals */
char        *lineptr[MAXLINES];   /* pointers to text lines */
static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */
int         numeric = 0;          /* 1 if numeric sort */
int         decreasing = 0;       /* 1 if reverse order sort */
int         fold = 0;             /* 1 id case insensitive sort */

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}
	if ( c == '\n') {
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
	while ((len = getLine(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';   /* delete newline character */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* alloc: allocate memory */
char *alloc(int n)               /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >=n) {     /* it fits */
		allocp += n;
		return allocp - n;                       /* old p */
	} else                                       /* not enough room */
		return 0;
}

/* qsort: sort v[left]...V[right] into increasing order */
void qSort(void *v[], int left, int right,
		int (*comp)(void *, void *))
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
	else if (v1 > v2)
		return 1;
	else
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

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* reverse: reverse the return value of a function */
int reverse(char *s, char *t)
{
	int (*compfun) (char *, char *);  /* pointer to compare function */

	compfun = (numeric) ? numcmp : (fold) ? fstrCmp : strCmp;

	if ((*compfun)(s, t) < 0)
		return  1;
	else if ((*compfun)(s, t) > 0)
		return -1;
	return 0;
}

/* fstrCmp: same as strCmp but case insensitive */
int fstrCmp(char *s, char *t)
{
	for ( ; tolower(*s) == tolower(*t); s++, t++)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;               /* number of input lines read */     

	while (--argc > 0) {
		++argv;
		if (strCmp(argv[0], "-n") == 0)
			numeric = 1;
		if (strCmp(argv[0], "-r") == 0)
			decreasing = 1;
		if (strCmp(argv[0], "-f") == 0)
			fold = 1;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
			qSort((void**) lineptr, 0, nlines - 1, 
					(int (*)(void *, void *))(decreasing ? reverse : numeric ?
						numcmp : fold ? fstrCmp : strCmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}
