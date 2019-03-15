/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

/* getLine (Chapter 1) */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* functions */
int getLine(char *, int);

/* getLine function: read a line into s, return length - pointer version */
int getLine(char *s, int lim)
{
	int c;
	char *len;

	len = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';

	return strlen(len);
}

int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0) {
		printf("%s", line);
	}
	return 0;
}
