/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it
 * will correctly print the length of arbitrary long input lines, and as much
 * as possible of the text.
 * Note: changed getline() name to getLine().
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE 1000          /* maximum input line length */

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
	int  len;                 /* current line length */
	int  max;                 /* maximum length seen so far */
	char line[MAXLINE];       /* current input line */
	char longest[MAXLINE];    /* longest line saved here */

	max = 0;
	while ((len = getLine(line, MAXLINE)) > 0)
		if (len == MAXLINE - 1 &&   /* test for length and previous input */
				line[MAXLINE - 1] != '\n') {
			copy(longest, line);            /* save the string */
			longest[MAXLINE - 2] = '\n';    /* insert a newline character before
											   the null character */
			max = len;
			max += getLine(line, MAXLINE); /* save the value of max */
		} else if (len > max) {
			max = len;
			copy(longest, line);
		}

	if (max > 0)                            /* there was a line */
		printf("%s", longest);

	if (max >= MAXLINE - 1) {               /* print warning message */
		printf("Warning: The longest line is %i characters long.\n", max);
		printf("\t  Only showing the first %i characters\n", MAXLINE);
	}
	return 0;
}
