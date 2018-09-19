/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 * by Faisal Saadatmand
 */

#include <stdio.h>

int main(void)
{
	int c, blank, tab, nl;

	blank = tab = nl = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++blank;
		if (c == '\t')
			++tab;
		if (c == '\n')
			++nl;
	}

	printf("%d blanks, %d tabs, %d newlines\n", blank, tab, nl);

	return 0;
}

