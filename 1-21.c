/* 
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. When either a
 * tab or a singl blank would suffice to reach a tab stop, which should be give
 * preference?
 * By Faisal Saadatmad
 */

/*
 * Answer: in such a case, a singal space is given preference, because otherwise a change 
 * to the value of the tab stop (n) would distored the single space.
 */

#include <stdio.h>

#define MAXLINE 1000
#define N       4             /* default tabstop for every n columns */
#define YES     1
#define NO      0

/* functions declarations */
int  getLine(char s[], int lim);
int  count(char s[], char c, int p);
void entab(char line[], char modLine[]);

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

/* count function: counts the occurremces of a character in a string */ 
int count(char s[], char c, int p)
{
	int nC = 0;               /* number of c occurrences in s[] */
	while (s[p] == c) {
		++p;
		++nC;
	}
	return nC;
}

/* entab function: replaces blanks with the minimum of number tabs and blanks */
void entab(char line[], char modLine[])
{
	int i;                    /* index for read line */
	int j = 0;                /* index for modified (written) line */
	int toTabStop;            /* number of blanks to the next tab stop */
	int blanks;               /* size of the string of blanks */
	int copyChar;             /* control flag: write to modline */

	for (i = 0; line[i] != '\0'; ++i) {
		copyChar = YES;
		if (line[i] == ' ') {
			toTabStop = N - (i % N);
			blanks = count(line, ' ', i);
			if (blanks > toTabStop) /* roll back counter to the last tab stop */
				blanks = toTabStop;
			if (blanks >= 2 && blanks >= toTabStop) { /* skip single blanks and
														  not tab blanks */
				modLine[j] = '\t';
				++j;
				i += toTabStop - 1;
				copyChar = NO;
			}
		}
		if (copyChar) {
			modLine[j] = line[i];
			++j;
		}
	}
	modLine[j] = '\0';
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
