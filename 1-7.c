/* 
 * copy input to output
 * Modification:  print the value of EOF
 */

#include <stdio.h>

int main(void)
{
	int c;

	while ((c = getchar()) != EOF)
		;                                  /* null statement, but any 
											  other statement would work too */

	printf("value of EOF is %i\n", c);     /* print the value of EOF */

	return 0;
}
