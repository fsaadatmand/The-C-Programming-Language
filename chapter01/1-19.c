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
void reverse(char []);

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

/* reverse: reverses s's charaters in-place. */
void reverse(char s[])
{
	int i, j, len, temp;

	len = 0;
	for (i = 0; s[i] != '\0'; ++i)
		++len;

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
		reverse(line);
		printf("%s\n", line);
	}
	return 0;
}
