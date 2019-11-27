/* 
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. When either a
 * tab or a single blank would suffice to reach a tab stop, which should be give
 * preference?
 *
 * By Faisal Saadatmand
 */

/*
 * Answer: with this implementation a tab is inserted when only 1 space is
 * needed to the next tab stop. See line 51 below. This way we don't have worry
 * about any special cases.
 */

#include <stdio.h>

#define MAXLEN 1000
#define N 4 /* default tabstop for every n columns */

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
void entab(char in[], char out[])
{
	int i; /* index for read line */
	int j; /* index for modified (written) line */
	int nblanks; /* number of required blanks */
	int ntabs; /* number of required tabs */
	
	for (i = j = 0; in[i] != '\0'; ++i) {
		if (in[i] == ' ') {
			for (nblanks = ntabs = 0; in[i] == ' '; ++i) { /* count blanks */
				if ((i + 1) % N == 0) { /* replace every N blanks with a tab */
					++ntabs;
					nblanks = 0; /* reset */
				} else
					++nblanks;
			}
			--i; /* adjust position after the loop */
			while (ntabs-- > 0) /* insert tabs */
				out[j++] = '\t';
			while (nblanks-- > 0) /* insert remaining blanks */
				out[j++] = ' ';
		} else 
			out[j++] = in[i]; /* copy all other characters */
	}
	out[j] = '\0';
}

int main(void)
{
	char in[MAXLEN]; /* currently read line */
	char out[MAXLEN]; /* modified line */

	while (getLine(in, MAXLEN) > 0) {
		entab(in, out);
		printf("%s", out);
	}
	return 0;
}
