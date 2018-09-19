/* 
 * Exercise 1-7. Write a program to print the value of EOF.
 * By Faisal Saadatmand
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
