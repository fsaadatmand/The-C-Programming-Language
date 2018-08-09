#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

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

int expand(char s1[], char s2[])
{
	int i, j, trailing, position, foundMatch;
	char minus = '-';

//	do {
//			position = ++i;               
//	} while (s1[i] != ' ');         /* first occurrence of - in s1 */

	for (i = 0; s1[i] != '\0'; ++i) {
		if (line[i] == minus && line[i - 1] != ' ') {
			foundMatch = 0;
			for (j = i + 1; s1[j] != '\0' && foundMatch != 1; ++j)
				if (s1[j] == minus) 
					if (s1[j - 1] == ' ')
						trailing = 1;
					else {
						position = j;
						foundMatch = 1;
					}

		}
	}
	return position;
}
int main(void)
{
	int position;
	char line[MAXLINE] = { " -a thi-s a test for a-b.\n" };
	char modLine[MAXLINE];

	printf("%i\n", expand(line, modLine));
	
	return 0;
}
