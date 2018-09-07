/* 
 * Exercise 5-11. Modify the program and detab (written in exercises in Chapter
 * 1) to accept a list of tab stops as arguments. Use the default tab setting
 * if there are no arguments.
 * By Faisal Saadatmad
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXARG  20                  /* max number of tabstop arguments */

/* functions declarations */
int getLine(char *s, int lim);
void detab(char *line, char *modLine, int *n);

/* Global variables */
int n = 4;                          /* default tabstop for every n columns */
int argNum = 0;                     /* number of command-line arguments */ 

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

/* detab function: replaces tabs with the proper number of blanks; reads from
 * line, writes to modLine. Tabstop every n column. */
void detab(char *line, char *modLine, int *n)
{
	int toNextTabStop;              /* number of spaces to the next tabstop */
	int column;                     /* current column number/location */
	int nTabStops;                  /* counter to cycle throught tabList[] */

	nTabStops = argNum;
	column = 0;
	while (*line != '\0') {
		if (*line == '\t') {
			toNextTabStop = *n - (column % *n);
			while (toNextTabStop-- > 0) {
				*modLine++ = ' ';
				++column;
			}
			if (--nTabStops > 0)    /* keep last setting, if no more element */
				++n;                /* switch to next tabstop in the list */
		} else {
			*modLine++ = *line;
			++column;
		}
		++line;
	}
	*modLine = '\0';
}

int main(int argc, char *argv[])
{
	char line[MAXLINE];             /* currently read line */
	char modLine[MAXLINE];          /* modified line */
	static int tabList[MAXARG];     /* list of tabstops */
	int i;                          /* *argv[] elements index */
	int *pTablist, *pN;             /* convenient pointers */

	pTablist = tabList;

	argNum = argc - 1;              /* record number of cli arguments */

	if (argNum > MAXARG) {          /* tabStops[] #arguments limit check */
		printf("error: %d max number of tab stops\n", MAXARG);
		return -1;
	}

	while (--argc > 0) {            /* check for cli arguments */
		++argv;
		for (i = 0; (*argv)[i] != '\0'; ++i) /* error check; non-digits input */
			if (!isdigit((*argv)[i])) {
				printf("error: invalid argument\n");
				return -1;
			}

		*pTablist = atoi(*argv);    /* store tabstops list */

		if (*pTablist <= 0) {       /* error check; 0 & negative numbers */
			printf("error: zero is an invalid tabstop value\n");
			return -1;
		}
		++pTablist;
	}

	pN = (!argNum) ? &n : tabList;  /* if no cli arguments, 
									   use default tabstop setting */
	while (getLine(line, MAXLINE) > 0) {
		detab(line, modLine, pN);
		printf("%s", modLine);
	}
	return 0;
}
