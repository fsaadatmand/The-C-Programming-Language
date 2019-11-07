/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 *
 * by Faisal Saadatmand
 */

#include <stdio.h>

int main(void)
{
	int c, blanks, tabs, newlines;

	blanks = tabs = newlines = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++blanks;
		if (c == '\t')
			++tabs;
		if (c == '\n')
			++newlines;
	}

	printf("%d blanks, %d tabs, %d newlines\n", blanks, tabs, newlines);

	return 0;
}

