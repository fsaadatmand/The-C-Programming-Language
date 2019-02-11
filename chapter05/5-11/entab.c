/* 
 * Exercise 5-11. Modify the program and detab (written in exercises in Chapter
 * 1) to accept a list of tab stops as arguments. Use the default tab setting
 * if there are no arguments.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MAXARG  20                  /* max number of tabstop arguments */

/* Global variables */
int n = 4;                          /* default tabstop for every n columns */

/* functions declarations */
int  getLine(char *s, int lim);
int  count(char *s, char c);
int  isDigitStr(char *s[]);
void entab(char *line, char *modLine, int *list, int listSize);

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

/* count function: counts the occurrences of a character in a string - pointer
 * version */ 
int count(char *s, char c)
{
	int nC = 0;               /* number of c occurrences in s[] */

	while (*s++ == c)
		++nC;

	return nC;
}

/* isDigitStr: check if string is made of positive integers characters. Return
 * 1 if true; 0 if false */
int isDigitStr(char *s[])
{
	int i;

		for (i = 0; (*s)[i]; ++i)   /* omitted '\0', since s is a pointer */
			if (!isdigit((*s)[i]))
				return 0;
	return 1;
}

/* entab function: replaces blanks with the minimum of number tabs and blanks */
void entab(char *line, char *modLine, int *list, int listSize)
{
	int toNextTabStop;        /* number of blanks to the next tab stop */
	int column;               /* current column number/location */
	int spaces;               /* size of the string of blanks */
	int nTabs;                /* number of tabs to replace blanks */
	int nblanks;              /* number of remaining blanks */

	column = 0;	
	while (*line != '\0') {
		if ((spaces = count(line, ' ')) > 1) {   /* count blank characters */

			while (column >= *list && listSize > 0) { /* find column in list */
				++list;
				--listSize;
			}
			if (listSize > 0)
				toNextTabStop = *list - column;
			else
				toNextTabStop = n - (column % n); /* default tab stop setting */

			nTabs = spaces / n;                  /* number of needed tabs */
			nblanks = spaces % n;                /* remaining blanks */ 

			if (toNextTabStop < n) {
				++nTabs;
				nblanks = 0;
			}
			if (toNextTabStop == n) {
				*modLine++ = ' ';
				--nblanks;
			}

			while (nTabs-- > 0)                   /* insert tab(s) */
				*modLine++ = '\t';

			while (nblanks-- > 0)                 /* insert blank(s) */
				*modLine++ = ' ';

			line += spaces;                       /* skip spaces */
			column += spaces;                     /* track column position */

		} else {
			*modLine++ = *line++;
			++column;
		}
	}
	*modLine = '\0';
}

int main(int argc, char *argv[])
{
	char line[MAXLINE];              /* currently read line */
	char modLine[MAXLINE];           /* modified line */
	static int tabStopList[MAXARG];  /* list of tab stops (column numbers) */
	int tabStopsNumb;                /* number of command-line arguments */ 
	int *pTablist;                   /* pointers to tabStopList */
	int type;                        /* type of argument operator */

	pTablist = tabStopList;
	tabStopsNumb = 0;
	while (--argc > 0) {
		type = *(++argv)[0];
		switch (type) {
		case ('-'):
			if (*++argv[0] == 'l' && (int) strlen(*argv) == 1) {
				while (--argc > 0)
					if (isDigitStr(++argv)) {
						*pTablist++ = atoi(*argv);  /* store tab stops list */
						tabStopsNumb += 1;
					} else {
						printf("detab: invalid tab stop setting %s\n", *argv);
						return -1;
					}
			} else {
				printf("detab: illegal option %s\n", *argv);
				return -1;
			}
			break;
		default:
			printf("detab: illegal operator %c\n", *argv[0]);
			return -1;
			break;                 /* superfluous */
		}
	}
	while (getLine(line, MAXLINE) > 0) {
		entab(line, modLine, tabStopList, tabStopsNumb);
		printf("%s", modLine);
	}
	return 0;
}
