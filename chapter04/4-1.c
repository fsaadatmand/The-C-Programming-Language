/*
 * Exercise 4-1. Write the function strindex(s,t) which returns the position of
 * the rightmost occurrence of s in t, or -1 if there is none.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000          /* maximum input line length */

int getLine(char line[], int lim);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";      /* pattern to search for */

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
int strindex(char s[], char t[])
{
	int i, j, k;
	
	for (i = strlen(s); i >= 0; i--) {  /* read the string backwards */
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}

	return -1;
}

/* find all lines matching pattern */
int main(void)
{
	char line[MAXLINE];
	int found = 0;
	int position; 

	while (getLine(line, MAXLINE) > 0)
		if ((position = strindex(line, pattern)) >= 0) {
			printf("%s", line);
			printf("%i\n", position);
			found++;
		}
	return found;
}
