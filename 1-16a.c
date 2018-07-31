/* 
 * Program to print the longest line
 * Note: change function name from getline to readline 
 * Modified the readline function and the main routine. 
 * While this approach works, it is not the correct answer for 
 * question 1-16.
 */

#include <stdio.h>

#define MAXLINE 1000          /* maximum input line length */

int readline(char s[], int lim);
void copy(char to[], char from[]);

/* readline function: read a line into s, return length */
int readline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (i == lim - 1)
	{
		while ((c = getchar()) != EOF && c != '\n')
			++i;
	}

	if (c == '\n' && i < lim - 1) {
		s[i] = c;
		++i;
	} else if (c == '\n' && i > lim - 1) {
		s[lim - 2] = '\n';
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
	int len;                  /* current line length */
	int max;                  /* maximum length seen so far */
	char line[MAXLINE];       /* current input line */
	char longest[MAXLINE];    /* longest line saved here */

	max = 0;

	while ((len = readline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	
	if (max > 0)              /* there was a line */
		printf("%s", longest);

	if (max > MAXLINE) {
		printf("The longest line is %i characters long.\n", max); 
		printf("Only showing the first %i characters\n", MAXLINE);
	}

	return 0;
}

