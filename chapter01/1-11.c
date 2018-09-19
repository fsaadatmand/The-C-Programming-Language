/*
* Exercise 1-11. How would you test the word count program? What kinds of input
* are most likely to uncover bugs if there are any?
* By Faisal Saadatmand
*/

#include <stdio.h>

#define IN  1    /* inside a word */
#define OUT 0    /* outside a word */

int main(void)
{
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;

	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
	return 0;
}
