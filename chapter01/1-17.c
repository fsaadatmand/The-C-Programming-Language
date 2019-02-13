/*
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */
#define NCHARS        82           /* number of chars per line, including
									  the newline and null characters */

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
	int  len;                 /* current line length */
	char line[MAXLINE];       /* current input line */

	while ((len = getLine(line, MAXLINE)) > 0)
		if (len > NCHARS)
			printf("%s", line);
	return 0;
}
