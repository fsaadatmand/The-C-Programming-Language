/* 
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
int lower(char c);

/* lower: convert c to lower case; ASCII only */
int lower(char c)
{ 
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(void)
{
	char c;

	while ((c = getchar()) != EOF)
			printf("%c", lower(c));
	return 0;
}
