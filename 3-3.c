#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MINUS '-'
#define SPACE ' '
#define TAB '\t'
#define COMMA ','
#define DOT '.'

/* readline function: read a line into s, return length */
int readline(char s[], int lim)
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

int expand(char s1[], char s2[]) {
	int i;
	int j;
	int p;
	int position;
	int isShortHand;

	isShortHand = 0;
	for (i = 0, j = 0; s1[i] != '\0'; ++i) {
		if (s1[i - 1] != MINUS && s1[i - 1] != MINUS)
			if (s1[i] == MINUS)
				if (isalnum(s1[i - 1]) && isalnum(s1[i + 1]))
					if (isspace(s1[i - 2]) && isspace(s1[i + 2])) {
						isShortHand = 1;
						position = i;
					}

		if (isShortHand == 1) {
			--j;
			for (p = s1[position - 1]; p <= s1[position + 1]; ++p) {
				s2[j] = p;
				++j;
				isShortHand = 0;
			}
			--j;
			++i;
		} else
			s2[j] = s1[i];
			++j;
	}
	s2[j] = '\0';
}

int main(void)
{
//	int len;
	char line[MAXLINE];
	char modLine[MAXLINE];

	while (readline(line, MAXLINE) > 0)
		expand(line, modLine);
		printf("%s", modLine);
	return 0;
}
