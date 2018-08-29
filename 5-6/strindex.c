/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 * */

#include <stdio.h>

#define MAXLINE 1000          /* maximum input line length */

int getLine(char *line, int lim);
int strindex(char *source, char *searchfor);

char pattern[] = "ould";      /* pattern to search for */

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

/* strindex: return index of t in s, -1 if none - pointer version */
int strindex(char *s, char *t)
{
	int index;
	char *j, *k;
	
	index = 0;
	while (*s != '\0') {
		j = s;
		k = t;
		while (*k != '\0' && *j++ == *k++)
			;
		if (k > t && *k == '\0')
			return index;
		++index;
		++s;
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
