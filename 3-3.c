#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
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

void expand(char s1[], char s2[])
{
	int i;                /* current input line index */
	int j;                /* current output line index */
	int p;                /* temp index for minus positon */
	int position = 0;         /* position of the minus char */
	int notShortHand = 0;
	int isShortHand = 0;
	char minus = '-';


	for (i = 0; s1[i] != '\0'; ++i) {
		if (s1[i] == minus && s1[i - 1] != SPACE && s1[i + 1] != SPACE)  /* skip leading & trailing minus */
			if (s1[i - 2] == SPACE || s1[i - 2] == TAB && s1[i + 2] == SPACE || s1[i + 2] == '\t') {
				isShortHand = 1;
				position = i;
			}
//			else
//				for (p = i + 1; s1[p] != ' ' && s1[p] != '\t'; ++p)     /* check for more minuses - */
//					if (s1[p] == minus)
//						isShortHand = 0;
//					else {
//						isShortHand = 1;
//						position = i;
//					}

		if (isShortHand) {
			for (p = s1[position - 1]; p < s1[position + 1]; ++p) {
				s2[j] = p;
				++j;
			}
			++i;
		} else
			s2[j] = s1[i];
		++j;
	}
}
int main(void)
{
	int position;
	char line[MAXLINE] = { " -a th-i-s a-b is a test for a-b.\n" };
	char modLine[MAXLINE];

	expand(line, modLine);
	printf("%s\n", modLine);
	
	return 0;
}
