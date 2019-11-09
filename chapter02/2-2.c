/*
 * Exercise 2-2. Write a loop equivalent to the for loop above without using &&
 * or ||. 
 *
 * By Faisal Saadatmand
 */

/*
 * 		for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * 			s[i] = c;
 *
 * 	NOTE: expressions connected by logical operators are evaluated left to
 * 	right.
*/
#include <stdio.h>

#define MAXLINE 1000         /* maximum input line length */

/* functions */
int getLine(char [], int);

/* getLine function: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i, halt;

	halt = 0;
	for (i = 0; !halt; ++i) {
		if (i > lim - 1)
			halt = 1;
		else if ((c = getchar()) == '\n')
			halt = 1;
		else if (c == EOF)
			halt = 1;
		else
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
	char line[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
		printf("%s", line);

	return 0;
}
