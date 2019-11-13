/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input.
 *
 * By Faisal Saadatmand
 */

/* Vertical Histogram. See 1-14.c for a horizontal histogram implementation */

#include <stdio.h>

#define SIZE 93 /* size of characters array */
#define SCALE 1 /* adjust to accommodate large input */

int main(void)
{
	int c, i, count, longestBar;
	int characters[SIZE];

	/* initialize elements' values to 0 */
	for (i = 0; i < SIZE; ++i)
		characters[i] = 0;

	count = 0;
	while ((c = getchar()) != EOF) 
		/* match graphical characters only (ASCII table) */
		if (c >= '!' && c <= '~') {
			++characters[c - '!'];
			++count; /* number of matched characters */
		}

	if (!count)
		return -1;

	printf("\nVertical Histogram:\n");

	/* find the longestBar */
	longestBar = 0;
	for (i = 0; i < SIZE; ++i)
		if (characters[i] > longestBar)
			longestBar = characters[i];
	longestBar /= SCALE;

	/* print vertical histogram  */
	while (longestBar > 0) {
		for (i = 0; i < SIZE; ++i)
			if (characters[i] != 0) { /* skip if no data */
				if (characters[i] / SCALE < longestBar)
					printf(" %c", ' ');
				else
					printf(" %c", '*');
			}
		printf("\n");
		--longestBar;
	}

	/* print labels */
	for (i = 0; i < SIZE; ++i)
		if (characters[i] != 0) /* skip if no data */
			printf (" %c", i + '!');
	printf("\n");

	return 0;
}
