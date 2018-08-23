/*
 * Exercise 4-14. Define a macro swap(t, x, y) that interchanges two arguments
 * of type t. (Block structure will help).
 * By Faisal Saadatmand
 */

#include <stdio.h>


#define SWAP(t, x, y) if (sizeof(x) == sizeof(t) && sizeof(y) == sizeof(t)) \
{t temp = (x); temp = (x),  (x) = (y), (y) = temp;}

/* alternatively we can use bitwise XOR 
#define SWAP(t, x, y) if (sizeof(x) == sizeof(t) && sizeof(y) == sizeof(t)) \
{(x) ^= (y), (y) ^= (x), (x) ^= (y);}
*/

int main(void)
{
	int a = 6;
	int b = 3;

	printf("Before SWAP a = %i b = %i\n", a, b);

	SWAP(int, a, b);

	printf("After  Swap a = %i b = %i\n", a, b);

	return 0;
}
