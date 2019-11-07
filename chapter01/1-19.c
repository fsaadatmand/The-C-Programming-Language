/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a
 * time.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */

/* functions */
int  getLine(char [], int);
void reverse(char [], char [], int);
void emplace_reverse(char [], int);

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

/* reverse function: copy the charaters of  s1 into s2 in reverse order */
void reverse(char s1[], char s2[], int len)
{
	int i;

	--len; /* skip the null character '\0' */
	for (i = 0; s1[i] != '\0'; ++i, --len)
		s2[len] = s1[i];

	s2[i] = '\0';
}

/* emplace_reverse: reverses s's charaters in-place. */
void emplace_reverse(char s[], int len)
{
	int i, j, temp;

	for (i = 0, j = len - 1; i < len / 2; ++i, --j) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

int main(void)
{
	int  len;                   /* current line length */
	char line[MAXLINE];         /* current input line */

	while ((len = getLine(line, MAXLINE)) > 0) {
		line[--len] = '\0';     /* remove newline character at the end */
		emplace_reverse(line, len);
		printf("%s\n", line);
	}
	return 0;
}
