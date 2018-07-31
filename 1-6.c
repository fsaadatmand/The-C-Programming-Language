/* 
 * copy input to output
 * Verify that the expression getchar() != EOF is 0 or 1
 */

#include <stdio.h>

int main(void)
{
	int c;

	while (c = getchar() != EOF)    /* note operator precedence */
		printf("%i\n", c);
		
	printf("%i\n", c);

	return 0;
}
