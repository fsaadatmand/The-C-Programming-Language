/* 
 * Exercise 5-12. Extend entab and detab to accpt the shorthand
 * 	entab -m +n
 * 	to mean tab stops every n columns, starting at column m. Choose convenient
 * 	(for the user) default behavoir.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MAXARG  1000                /* max number of tab stop arguments */

/* functions declarations */
int  getLine(char *s, int lim);
int  isDigitStr(char *s[]);
void detabList(char *line, char *modLine, int *list, int listSize);

/* Global Variables */
int n = 4;                          /* default tab stop for every n columns */

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

/* detabList function: replaces tabs with the proper number of blanks; reads from
 * line, writes to modLine. Uses default tab stop (every N column) if no list.
 * is supplied */
void detabList(char *line, char *modLine, int *list, int listSize)
{
	int toNextTabStop;              /* number of spaces to the next tab stop */
	int column;                     /* current column number/location */

	column = 0;                     /* must starts at 0 or algorithm breaks */
	while (*line) {
		if (*line == '\t') {
			while (column >= *list && listSize > 0) {  /* find column in list */
				++list;
				--listSize;
			}
			if (listSize > 0)
				toNextTabStop = *list - column;
			else
				toNextTabStop = n - (column % n); /* default tab stop setting */

			while (toNextTabStop-- > 0) {
				*modLine++ = ' ';
				++column;
			}
		} else {
			*modLine++ = *line;
			++column;
		}
		++line;
	}
	*modLine = '\0';
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

int main(int argc, char *argv[])
{
	char line[MAXLINE];             /* currently read line */
	char modLine[MAXLINE];          /* modified line */
	static int tabStopList[MAXARG]; /* list of tab stops (column numbers) */
	int tabStopsNumb;               /* number of entered tab stops */ 
	int *pTablist;                  /* pointer to tabStopList */
	int type;                       /* type of argument operator */
	int mShorthand,nShorthand;      /* flag variables */            
	int c;                          /* temp variable to increment pointer */

	pTablist = tabStopList;

	mShorthand = nShorthand = tabStopsNumb= 0;
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
			} else if  (isdigit(*argv[0])) {
				if (isDigitStr(argv) && !mShorthand) {
					mShorthand = 1;
					*pTablist = atoi(*argv);  /* store tabs tops list */
					tabStopsNumb = 1;
				} else {
					printf("detab: illegal shorthand -%s\n", *argv);
					return -1;
				}
			} else {
				printf("detab: illegal option %s\n", *argv);
				return -1;
			}
			break;
		case ('+'):
			c = *++argv[0];
			if (isDigitStr(argv) && !nShorthand) {
				nShorthand = 1;
				n = atoi(*argv);
			} else {
				printf("detab: illegal shorthand +%s\n", *argv);
				return -1;
			}
			break;
		default:
			printf("detab: illegal operator %c\n", *argv[0]);
			return -1;
			break;                        /* superfluous */
		}
	}
	
	while (getLine(line, MAXLINE) > 0) {
		detabList(line, modLine, tabStopList, tabStopsNumb);
		printf("%s", modLine);
	}
	return 0;
}
