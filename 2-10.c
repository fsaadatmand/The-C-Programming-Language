/* 
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */

int  getLine(char s[], int lim);
void toLowercase(char line[]);

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

void toLowercase(char line[])
{ 
	int  i;

	for (i = 0; line[i] != '\0'; ++i)
		line[i] = (line[i] >= 'A' && line[i] <= 'Z') ? (line[i] + 'a' - 'A')
			: line[i];
}

int main(void)
{
	char len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0) {
		toLowercase(line);
		printf("%s", line);
	}
	return 0;
}
