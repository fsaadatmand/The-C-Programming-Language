/*
 *Exercise 3-2. Write a function escape(s,t) that converts characters like
 newline and tab into visible escape sequences like \n and \t as it copies the
 string t to s. Use a switch. Write a function for the other direction as well,
 converting escape sequences into the real characters. 
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE       10000         /* maximum input line length */

/* functions */
int  getLine(char [], int);
void escape(char [], char []);
void escapeRev(char [], char []);

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

void escape(char line[], char modLine[])
{
	int i, j = 0;

	for (i = 0; line[i] != '\0'; ++i) {
		switch (line[i]) {
		case '\t':
			modLine[j] = '\\';
			modLine[j + 1] = 't';
			++j;
			break;
		case '\n':
			modLine[j] = '\\';
			modLine[j + 1] = 'n';
			++j;
			break;
		default:
			modLine[j] = line[i];
			break;
		}
		++j;
	}
	modLine[j] = '\0';
}

void escapeRev(char line[], char modLine[])
{
	int i, j = 0;

	for (i = 0; line[i] != '\0'; ++i) {
		switch (line[i]) {
		case '\\':
			switch (line[i + 1]) {
			case 't':
				modLine[j] = '\t';
				++i;
				break;
			case 'n':
				modLine[j] = '\n';
				++i;
				break;
			default:
				modLine[j] = line[i];
				break;
			}
			break;
		default:
			modLine[j] = line[i];
			break;
		}
		++j;
	}
	modLine[j] = '\0';
}

int main(void)
{
	char len;
	char line[MAXLINE];
	char modLine[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0) {
	//	escape(line, modLine);
	//	printf("%s", modLine);
		escapeRev(line, modLine);
		printf("%s", modLine);
	}
	return 0;
}
