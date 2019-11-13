/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging.
 *
 * By Faisal Saadatmand
 */

/* Vertical Histogram. See 1-13.c for a horizontal histogram implementation */

#include <stdio.h>

#define SIZE 5    /* size of lengths array */
#define SCALE 1   /* adjust to accommodate large input */
#define OUT  1    /* outside of a word */
#define IN   0    /* inside of a word */

int main(void)
{
	int c, i, count, state, longestBar; 
	int lengths[SIZE]; /* words length ranges */

	for (i = 0; i <= SIZE; ++i)
		lengths[i] = 0;

	state = OUT;
	count = 0;
	while ((c = getchar()) != EOF) {

		if (c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else
			state = IN;

		if (state == IN)
			++count;

		if (state == OUT) {
			if (count < 4)
				++lengths[0];
			else if (count >= 4 && count < 8)
				++lengths[1];
			else if (count >= 8 && count < 12)
				++lengths[2];
			else if (count >= 12 && count < 14)
				++lengths[3];
			if (count >= 14)
				++lengths[4];
			count = 0;
		}
	}	

	printf("\nVertical Histogram:\n");
	longestBar = lengths[0];
	for (i = 0; i < SIZE; ++i)       /* find the longestBar */
		if (lengths[i] > longestBar )
			longestBar = lengths[i];
	longestBar /= SCALE;

	/* print vertical histogram  */
	while (longestBar > 0) {
		for (i = 0; i < SIZE; ++i)
			if (lengths[i] != 0) {
				if (lengths[i] / SCALE < longestBar)
					printf(" %2c", ' ');
				else
					printf(" %2c", '*');
			}
		printf("\n");
		--longestBar;
	}
	
	/* print value of each element (bar) */
	for (i = 0; i < SIZE; ++i)
		if (lengths[i] != 0)
			printf(" %2i", lengths[i]);
	printf("\n");

	return 0;
}			
