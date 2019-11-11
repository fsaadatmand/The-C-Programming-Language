/*
 * Exercise 4-1. Write the function strindex(s,t) which returns the position of
 * the rightmost occurrence of t in s, or -1 if there is none.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000          /* maximum input line length */

/* functions */
int getLine(char [], int);
int strindex(char [], const char []);

/* getLine: get line into s, return */
int getLine(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if ( c == '\n')
		s[i++] = c;

	s[i] = '\0';
	
	return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], const char t[])
{
	int i, j, k;
	
	for (i = strlen(s) - strlen(t); i >= 0; --i) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

int main(void)
{
	char line[MAXLEN];
	const char pattern[] = "ould"; 
	int pos; 

	while (getLine(line, MAXLEN) > 0)
		if ((pos = strindex(line, pattern)) < 0)
			printf("Not found\n");
		else
			printf("%i\n", pos);

	return 0;
}
