/*
 * Exercise 1-20. Write a program detab function that replaces tabs in the
 * input with the proper number of blanks to space to the next tab stop. Assume
 * a fixed set of tab stops, say every n columns. Should n be a variable or a
 * symbolic parameter.
 *
 * By Faisal Saadatmand
 */

/*
 * Answer: n should be a symbolic parameter, for the value of n should remain
 * constant throughout the duration of the program. A change in n would break
 * the algorithm.
 */

#include <stdio.h>

#define MAXLINE 1000
#define N       4          /* tabstop for every n columns */

/* functions */
int getLine(char [], int);

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

/* detab function: replaces tabs with the proper number of blanks */
void detab(char line[], char modLine[])
{
	int i;                    /* index for read line */
	int j;                    /* index for modified (written) line */
	int blanksToTabStop;      /* number of blanks to the next tab stop */

	for (i = j = 0; line[i] != '\0'; ++i)
		if (line[i] == '\t') {
			blanksToTabStop = N - (j % N);
			while (blanksToTabStop-- > 0)
				modLine[j++] = ' ';
		} else 
			modLine[j++] = line[i];
	modLine[j] = '\0';
}

int main(void)
{
	char line[MAXLINE];        /* currently read line */
	char modLine[MAXLINE];     /* modified line */

	while (getLine(line, MAXLINE) > 0) {
		detab(line, modLine);
		printf("%s", modLine);
	}
	return 0;
}
