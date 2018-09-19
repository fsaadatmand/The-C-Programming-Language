/*
 * Exercise 1-20. Write a program detab function that replaces tabs in the
 * input with the proper number of blanks to space to the next tab stop. Assume
 * a fixed set of tab stops, say every n columns. Should n be a variable or a
 * symbolic parameter.
 * By Faisal Saadatmad
 */

/*
 * Answer: it is wiser to use a symbolic parameter for the value n rather than
 * a gloabl variable. The value of n should remain constant throughout the
 * program, for a change in n would break algorithm in functions that depend on
 * a specific value of n. If need be, it is better to change the value of n in
 * a function through a local variable instead.
 */

#include <stdio.h>

#define MAXLINE 1000
#define N       4          /* tabstop for every n columns */

int getLine(char s[], int lim);
void detab(void);

char line[MAXLINE];        /* currently read line */
char modLine[MAXLINE];     /* modified line */

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
void detab(void)
{
	int i;                    /* index for read line */
	int j = 0;                /* index for modified (written) line */
	int toTabStop;            /* number of blanks to the next tab stop */

	for (i = 0; line[i] != '\0'; ++i)
		if (line[i] == '\t') {
			toTabStop = N - (j % N);
			while (toTabStop > 0) {
				modLine[j] = ' ';
				++j;
				--toTabStop;
			}
		} else {
			modLine[j] = line[i];
			++j;
			}
	modLine[j] = '\0';
}

int main(void)
{
	while (getLine(line, MAXLINE) > 0) {
		detab();
		printf("%s", modLine);
	}
	return 0;
}
