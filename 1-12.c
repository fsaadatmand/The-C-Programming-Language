/* program that prints its input one word per line */

#include <stdio.h>

int main(void)
{
	int c, 

	state = OUT;

	while ((c = getchar()) != EOF)
		if (c == ' ' || c == '\n' || c == '\t')
			printf("\n");
		else
			putchar(c);

	return 0;
}
