/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input.
 *
 * By Faisal Saadatmand
 */

/* Horizontal Histogram. See 1-14a.c for a vertical histogram implementation */

#include <stdio.h>

#define SIZE 93 /* size of characters array */
#define SCALE 1 /* adjust to accommodate large input */

int main(void)
{
	int c, i, j, count;
	int characters[SIZE];

	/* initialize elements' values to 0 */
	for (i = 0; i < SIZE; ++i)
		characters[i] = 0;

	count = 0;
	while ((c = getchar()) != EOF) 
		if (c >= '!' && c <= '~') { /* graphical characters only (ASCII table) */
			++characters[c - '!'];
			++count; /* number of matched characters */
		}

	if (!count)
		return -1;

	printf("\nHorizontal Histogram: (scale 1:%i)\n", SCALE);
	for (i = 0; i < SIZE; ++i)
		if (characters[i] != 0) { /* skip if no data */
			printf(" %c", i + '!'); /* labels */
			for (j = 1; j <= characters[i] / SCALE; ++j)
				printf(" *");
			printf("\n");
		}

	return 0;
}
