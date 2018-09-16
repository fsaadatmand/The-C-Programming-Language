/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE        1000        /* maximum input line length */
#define LINE_LENGTH    81          /* maximum output line length */

int    getLine(char s[], int lim);
void   foldLine(char line[], char fldLine[], int lineLen);

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

/* foldLine function: breaks line[] to a specified length lineLen and stores
 * results in fldLine[] */
void foldLine(char line[], char fldLine[], int lineLen)
{
	int i;                             /* position of currently read char */
	int nuChars = 0;                   /* line length counter */
	int wsPos = 0;                     /* position of the last whitespace */
	
	for (i = 0; line[i] != '\0'; ++i) {
		fldLine[i] = line[i];
		++nuChars;

		if (line[i] == ' ' || line[i] == '\t')
			wsPos = i;                 /* keep track of the prev ws position */

		if (nuChars == lineLen - 1) {
			/* check the end of line: */
			/* line is outside of a word or if is made up of one word. */
			if (line[i] == ' ' || line[i] == '\t' || wsPos == 0)
				fldLine[i] = '\n';     /* break line at current position */
			/* line is insdie of a word */
			else {
				fldLine[wsPos] = '\n'; /* break line at the previous ws */
				i = wsPos;             /* read from break point */
			}
			nuChars = 0;               /* reset line length counter */
		}
	}
	fldLine[i] = '\0';
}

int main(void)
{
	int  len;                 /* current line length */
	char line[MAXLINE];       /* current input line */
	char fldLine[MAXLINE];    /* folded input line */

	len = getLine(line, MAXLINE);
	while (len > 0) {
		if (len >= LINE_LENGTH) {
			foldLine(line, fldLine, LINE_LENGTH);
			printf("%s", fldLine);     /* print folded lines */
		} else	
			printf("%s", line);        /* print unfolded lines */
		len = getLine(line,MAXLINE);
	}
	return 0;
}
