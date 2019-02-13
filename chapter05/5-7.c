/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program? 
 * Answer: With the current implementation both clock_t and unix time command
 * report similar runtimes.  Perhaps a much bigger data would show a
 * discrepancy in runtimes.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES  5000       /* max #lines to be stored */
#define MAXLEN    1000       /* max length of any input line */
#define ALLOCSIZE 100000      /* storage for alloc */

/* functions */
int  readlines(char *[], int, char *);
void writelines(char *[], int);
int  getLine(char *, int);
void qsort(char *[], int, int);
void swap(char *[], int, int);

/* globals */
char *lineptr[MAXLINES];    /* pointers to text lines */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *p)
{
	int len, nlines, usedMemory;
	char line[MAXLEN];

	usedMemory = 0;
	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0)
		if (nlines >= maxlines || ALLOCSIZE - usedMemory < len)
			return -1;
		else {
			line[len - 1] = '\0';   /* delete newline character */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;               /* increment pointer */
			usedMemory += len;      /* track memory usage */
		}
	return nlines;
}

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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	
	if (left >= right)            /* do nothing if array contains */
		return;                   /* fewer than two elements */

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* sort lines */
int main(void)
{
	int nlines;                   /* number of input lines read */
	char memory[ALLOCSIZE];       /* stored lines */

	if ((nlines = readlines(lineptr, MAXLINES, memory)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
