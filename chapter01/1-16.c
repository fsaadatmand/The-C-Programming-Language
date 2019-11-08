/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrary long input lines, and print as
 * much as possible of the text.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLEN 1000       /* maximum input line length */

/* functionst */
int  getLine(char [], int);
void copy(char [], char []);

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

/* copy function: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) !='\0')
		++i;
}

int main(void)
{
	int len;                /* current line length */
	int nextLen;            /* next line length */
	int max;                /* maximum length seen so far */
	char line[MAXLEN];      /* current input line */
	char nextLine[MAXLEN];  /* next input line */
	char longest[MAXLEN];   /* longest line saved here */

	max = 0;
	while ((len = getLine(line, MAXLEN)) > 0) {
		if (len == MAXLEN - 1) { /* is line longer than buffer size? */
			line[MAXLEN - 1] = '\n';
			nextLen = len;
			while (nextLen == MAXLEN - 1) { /* find the line's length */
				nextLen = getLine(nextLine, MAXLEN);
				len += nextLen;
			}
		}
		if  (len > max) {
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0)             /* there was a line */
		printf("%s -> %i\n", longest, max);

	return 0;
}
