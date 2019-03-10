/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXCHAR 128
#define EMPTY 0

int main(void)
{
	int c, i, j, longestBar;
	int characters[MAXCHAR];

	for (i = 0; i <= MAXCHAR; i++)     /* initialize elements' values to 0 */
		characters[i] = 0;

	while ((c = getchar()) != EOF)
		if (c >= 32 && c <= 126)       /* graphical characters only */
			++characters[c - '0'];

	for (i = 0; i <= MAXCHAR; i++)     /* print value of each element (bar) */
		printf("%i ", characters[i]);
	printf("\n");

	printf("\nHorizontal Histogram:\n");

	for (i = 0; i <= MAXCHAR; i++) {
		if (characters[i] != EMPTY)    /* skip label if no data */
			printf("%c ", i + '0');    /* print histogram labels */
		for (j = 1; j <= characters[i]; j++)
			printf("* ");
		if (characters[i] != EMPTY)    /* skip character */
			printf("\n");
	}

	printf("\nVertical Histogram:\n");

	longestBar = characters[0];
	for (i = 0; i <= MAXCHAR; i++)     /* find the longestBar */
		if (longestBar < characters[i] )
			longestBar = characters[i];

	while (longestBar != 0) {          /* print vertical histogram  */
		for (i = 0; i <= MAXCHAR; i++)
			if (characters[i] != EMPTY) {
				if (characters[i] - longestBar < 0)
					printf("  ");
				else
					printf("* ");
			}
		--longestBar;
		printf("\n");
	}
	for (i = 0; i <= MAXCHAR; i++)     /* print histogram labels */
		if (characters[i] != EMPTY)
			printf ("%c ", i + '0');
	printf("\n");
	return 0;
}
