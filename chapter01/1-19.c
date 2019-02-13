/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a
 * time.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */
#define YES           1
#define NO            0

/* functions */
int  getLine(char [], int);
int  delTrailingWS(char [], int);
void reverse(char [], char [], int);

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

/* reverse function: reverses char string s1[] and store values into s[2] */
void reverse(char s1[], char s2[], int len)
{
	int i = 0;

	for (--len; s1[i] != '\0'; ++i) {
		s2[len] = s1[i];
		--len;
	}
	s2[i] = '\0';
}

int main(void)
{
	int  len;                   /* current line length */
	char line[MAXLINE];         /* current input line */
	char reversedLine[MAXLINE]; 

	while ((len = getLine(line, MAXLINE)) > 0) {
		len = delTrailingWS(line, len);   /* new length after removing ws */
		reverse(line, reversedLine, len);
		printf("%s", reversedLine);
	}
	printf("\n");
	return 0;
}
