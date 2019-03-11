/*
 * Exercise 2-2. Write a loop equivalent to the for loop above without using &&
 * or ||. 
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */

/* functions */
int getLine(char [], int);

/* getLine function: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i, halt = 0;

	for (i = 0; !halt; ++i) {          /* loop rewrite */
		if ((c = getchar()) == EOF)
			halt = 1;

		if (c == '\n')
			halt = 1;

		if (i > lim - 1)
			halt = 1;

		if (!halt)
			s[i] = c;
	}
	--i;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

int main(void)
{
	char line[MAXLINE];                /* current input line */

	while (getLine(line, MAXLINE) > 0)
		printf("%s", line);
	return 0;
}
