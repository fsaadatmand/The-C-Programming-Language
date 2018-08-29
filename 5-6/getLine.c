/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 * */

/* getLine (Chapter 1) */

#include <stdio.h>

#define MAXLINE 1000

/* getLine function: read a line into s, return length - pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	for (len = 0; len < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++len)
		*s++ = c;

	if (c == '\n') {
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

	while ((len = getLine(line, MAXLINE)) > 0) {
		printf("%s", line);
	}

	return 0;
}
