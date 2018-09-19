/*
 * Exercise 2-2. Write a loop equivalent to the for loop above without using &&
 * or ||. 
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */

int getLine(char s[], int lim);

/* getLine function: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i, halt = 0;

	c = getchar();
	for (i = 0; halt == 0; ++i) {
		if (c == EOF)
			halt = 1;

		if (c == '\n')
			halt = 1;

		if (i > lim - 1)
			halt = 1;

		if (halt == 0) {
			s[i] = c;
			c = getchar();
		}		
	}
	--i;

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
		printf("%s", line);
	return 0;
}
