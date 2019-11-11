/*
 * Exercise 3-3. Write a function expand(s1, s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be
 * prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
 * leading or trailing - is taking literally.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000

/* funstions */
int getLine(char [], int);
int isValidRange(char, char);
void expand(char [], char []);

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

/* isValidRange: check if begin and end make a valid range */
int isValidRange(char begin, char end)
{
	return begin < end && ((isdigit(begin) && isdigit(end))
			|| (isalpha(begin) && isalpha(end)
			&& ((islower(begin) && islower(end))
			|| (isupper(begin) && isupper(end)))));
}

void expand(char s1[], char s2[])
{
	int i, j, prevCh, nextCh, len;

	len = strlen(s1);
	for (i = 1, j = 0; s1[i] != '\0' ; ++i, ++j) { /* note that i starts at 1 */
		prevCh = s2[j] = s1[i - 1];  /* copy previous character */
		nextCh = s1[i + 1];
		if (len > 2 && s1[i] == '-' && isValidRange(prevCh, nextCh)) {
			while (++prevCh != nextCh)
				s2[++j] = prevCh; /* expand '-' into characters in-between */
			++i; /* skip '-' character */
		}
	}
	s2[j] = s1[i - 1]; /* copy the character before '\0' */
	s2[++j] = '\0';
}

int main(void)
{
	char line[MAXLEN];
	char modLine[MAXLEN];

	while (getLine(line, MAXLEN) > 0) {
		expand(line, modLine);
		printf("%s", modLine);
	}
	return 0;
}
