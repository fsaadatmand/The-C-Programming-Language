/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be
 * prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
 * leading or trailing  - is taking literally.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000
#define MINUS '-'

#define YES 1
#define NO  0

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

int expand(char s1[], char s2[])
{
	int i;                     /* read from s1 index */
	int j;                     /* write to s2 index */
	int expChar;               /* expanded charater */
	int shorthand;             /* shorthand match flag */
	int modified;              /* return value flag */

	modified = NO;
	for (i = 0, j = 0; s1[i] != '\0'; ++i) {
	shorthand = NO;
		if (s1[i] == MINUS)
			if (s1[i - 2] != MINUS && s1[i + 2] != MINUS) /* no leading/trailing - */
				if (isalnum(s1[i - 1]) && isalnum(s1[i + 1]))
					if (!isalnum(s1[i - 2]) && !isalnum(s1[i + 2])) {
						shorthand = YES;
						for (--j, expChar = s1[i - 1]; expChar <= s1[i + 1]; ++expChar) {
							s2[j++] = expChar;
							modified = YES;   /* optional */
						}
					}
	if (!shorthand)
		s2[j++] = s1[i];
	}

	s2[j] = '\0';

	return modified;
}

int main(void)
{
	char line[MAXLINE];
	char modLine[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
		if (expand(line, modLine))
			printf("%s", modLine);
		else
			printf("%s", line);

	return 0;
}
