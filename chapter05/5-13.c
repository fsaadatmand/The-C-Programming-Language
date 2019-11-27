/*
 * Exercise 5-13. Write the program tail. Which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that
 *
 * 		tail -n
 *
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or value of n. Write the program so it makes the best
 * use of available storage; lines should be stored as in the sorting program
 * of section 5.6, not in a two-dimensional array of fixed size.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000 /* max length of any input line */
#define MAXLINES 5000 /* max #lines to be stored */
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */


/* functions */
int getLine(char *, int);
char *alloc(int);
int readlines(char *[], int);
void writelines(char *[], int);
int expandArg(int, char **, int *);

/* getLine function: read a line into s, return length */
int getLine(char *s, int lim)
{
	int c;
	char *len;

	len = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return strlen(len);
}

/* alloc: return pointer to n characters */
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /*old p */
	}
	return NULL;  /* not enough room */
}

/* readlines: read input lines */
int readlines(char *linerptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		line[len - 1] = '\0'; /* delete newline */
		strcpy(p, line);
		linerptr[nlines++] = p;
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int expandArg(int count, char **list, int *n)
{
	char *prog = *list, *end;

	while (--count > 0)
		if (!strcmp(*++list, "-n")) {
			end = NULL;
			if (!(*n = strtol(*++list, &end, 10)) || *end) {
				printf("%s: invalid number of lines: %s\n", prog, *list);
				return 0;
			}
			*n = abs(*n); /* treat negative numbers as positives */
			--count;
		} else {
			printf("Usage: %s [-n lines]\n", prog);
			return 0;
		}
	return 1;
}

int main(int argc, char *argv[])
{
	char *lineptr[MAXLINES]; /* pointers to text lines */
	int nlines; /* number of read lines */
	int n = 10; /* default last n lines to print */ 

	if (!expandArg(argc, argv, &n))
		return -1;
	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		printf("Error: input is too big\n");
		return -1;
	}
	if (n > nlines) /* max limit check */
		n = nlines; /* print entire input, not more */
	writelines(lineptr + nlines - n, n); 
	return 0;
}
