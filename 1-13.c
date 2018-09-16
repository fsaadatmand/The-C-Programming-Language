/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define OUT  1    /* outside of a word */
#define IN   0    /* inside of a word */

int main(void)
{
	int c, i, j, nChar = 0, state, longestBar; 
	int lengths[10];

	for (i = 0; i <= 4; ++i)
		lengths[i] = 0;

	state = OUT;

	while ((c = getchar()) != EOF) {

		if (state == IN)
			++nChar;

		if (c == ' ' || c == '\t' || c =='\n') {
			if (state == IN) {
				if (nChar < 4)
					++lengths[0];
				else if (nChar >= 4 && nChar < 8)
					++lengths[1];
				else if (nChar >= 8 && nChar < 12)
					++lengths[2];
				else if (nChar >= 12 && nChar < 14)
					++lengths[3];
				if (nChar >= 14)
					++lengths[4];

				nChar = 0;
			}
		state = OUT;
		} else if (state == OUT)
			state = IN;
	}	

	/* print the value of each bar */
	for (i = 0; i <= 4; ++i)
		printf("%i ", lengths[i]);
	printf("\n");

	printf("\nHorizontal Histogram\n");
	for (i = 0; i <= 4; ++i) {
		for (j = 1; j <= lengths[i]; ++j)
			printf("* ");
		printf("\n");
	}

	printf("\nVertical Histogram:\n");
	longestBar = lengths[0];
	for (i = 0; i <= 4; ++i)                 /* find the longestBar */
		if (longestBar < lengths[i] )
			longestBar = lengths[i];

	while (longestBar != 0) {
		for (i = 0; i <= 4; ++i)
			if (lengths[i] - longestBar < 0)
				printf("  ");
			else
				printf("* ");
		--longestBar;
		printf("\n");
	}	
	return 0;
}			
