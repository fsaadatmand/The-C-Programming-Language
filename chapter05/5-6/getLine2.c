/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

/* getLine (Chapter 4) */

#include <stdio.h>

#define MAXLINE 1000

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}

	if ( c == '\n') {
		*s++ = c;
		++len;
	}

	*s = '\0';
	
	return len;
}

int main(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0)
		printf("%s", line);
	return 0;
}
