/*
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */
#define YES           1
#define NO            0

int  getLine(char s[], int lim);
int  delTrailingWS(char s[], int len);
void delBlankLns(char s[], int len);

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

/* delTrailingWS function: deletes trailing whitespaces and blank lines */
int delTrailingWS(char s[], int len)
{
	int i, blankLine;
	int newLength = len;      /* new length of line after whitespaces removal */

	i         = 0;
	blankLine = NO;

	/* test for blanklines with witespaces */
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		++i;
	if (i == len) {          /* remove whitespaces spaces form blank lines */
		s[0] = '\n';
		for (i = 1; s[i] != '\0'; ++i)
			s[i] = '\0';
		newLength -= i - 1;
	}

	if (s[0] == '\n') {
		blankLine = YES;
	}

	if (!blankLine) {          /* skip entirely blank lines */
		while (s[len] == '\0' || s[len] == '\n' ||
				s[len] == ' ' || s[len] == '\t') {
			s[len] = '\0';
			--len;
		}
		s[len + 1] = '\n';     /* insert newline char before null char */
		newLength = len + 2;   /* plus 2 for the newline and null characters */
	}
	return newLength;
}


/* delBlankLns function: deletes entirely blank lines */
void delBlankLns(char s[], int len)
{
	if (len == 1 && s[0] == '\n')
		s[0] = '\0';
}

int main(void)
{
	int  len;                 /* current line length */
	int  newLen;              /* modified line length */
	char line[MAXLINE];       /* current input line */

	while ((len = getLine(line, MAXLINE)) > 0) {
		newLen = delTrailingWS(line, len);
		delBlankLns(line, newLen);
		printf("%s", line);
	}
	return 0;
}
