/*
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLEN 1000    /* maximum input line length */
#define NCHARS 80       /* number of characters per line,
						   including the newline character */

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

int main(void)
{
	int  len;                /* current line length */
	char line[MAXLEN];       /* current input line */

	while ((len = getLine(line, MAXLEN)) > 0)
		if (len > NCHARS)
			printf("%s", line);
	return 0;
}
