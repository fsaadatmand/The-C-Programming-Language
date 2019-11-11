/*
 * Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction as
 * well, converting escape sequences into the real characters. 
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLEN 1000 /* maximum input line length */

/* functions */
int  getLine(char [], int);
void escape(char [], char []);
void escapeToChar(char [], char []);

/* getLine function: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* escape: copy string t to s and convert characters like newline and tab into
 * visible escape sequences */
void escape(char s[], char t[])
{
	int i, j;

	for (i = j = 0; t[i] != '\0'; ++i, ++j)
		switch (t[i]) {
		case '\t':
			s[j] = '\\';
			s[++j] = 't';
			break;
		case '\n':
			s[j] = '\\';
			s[++j] = 'n';
			break;
		default:
			s[j] = t[i];
			break;
		}
	s[j] = '\0';
}

/* escapeRev: copy string t to s and convert escape sequences like \n and \t
 * into newline and tab characters. */
void escapeToChar(char s[], char t[])
{
	int i, j;

	for (i = j = 0; t[i] != '\0'; ++i, ++j)
		switch (t[i]) {
		case '\\':
			switch (t[++i]) {
			case 't':
				s[j] = '\t';
				break;
			case 'n':
				s[j] = '\n';
				break;
			default:
				s[j] = t[i];
				break;
			}
			break;
		default:
			s[j] = t[i];
			break;
		}
	s[j] = '\0';
}

int main(void)
{
	char line[MAXLEN], modLine[MAXLEN];

	while (getLine(line, MAXLEN) > 0) {
		escape(modLine, line);
		printf("%s", modLine);
//		escapeToChar(modLine, line);
//		printf("%s", modLine);
	}
	return 0;
}
