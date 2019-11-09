/* 
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. When either a
 * tab or a single blank would suffice to reach a tab stop, which should be give
 * preference?
 *
 * By Faisal Saadatmand
 */

/*
 * Answer: a signal space is given preference, because otherwise a change to
 * the value of the tab stop (n) would distort the single space.
 */

#include <stdio.h>

#define MAXLINE 1000
#define N       4             /* default tabstop for every n columns */

/* functions */
int  getLine(char [], int);
void entab(char [], char []);

/* getLine function: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* entab function: replaces blanks with the minimum number of tabs and blanks */
void entab(char line[], char output[])
{
	int i;                    /* index for read line */
	int j = 0;                /* index for modified (written) line */
	int nblanks;              /* number of blanks in a series of blanks */
	int tabs, remaing_blanks;
	
	j = 0;
	for (i = 0; line[i] != '\0'; ++i) {
		if (line[i] == ' ') {
			nblanks = 1;
			/* count the number trailing blanks, if any */
			while (line[++i] == ' ')
				++nblanks;
			--i;
			tabs = nblanks / N;
			remaing_blanks = nblanks % N;
			/* insert tabs */
			while (tabs-- > 0)
				output[j++] = '\t';
			/* insert remaining blanks */
			while (remaing_blanks-- > 0)
				output[j++] = ' ';
		} else 
			output[j++] = line[i];
	}
	output[j] = '\0';
}

int main(void)
{
	char line[MAXLINE];       /* currently read line */
	char modLine[MAXLINE];    /* modified line */

	while (getLine(line, MAXLINE) > 0) {
		entab(line, modLine);
		printf("%s", modLine);
	}

	return 0;
}
