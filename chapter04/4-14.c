/*
 * Exercise 4-14. Define a macro swap(t, x, y) that interchanges two arguments
 * of type t. (Block structure will help).
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define SWAP(t, x, y) if (sizeof((x)) == sizeof(t) && sizeof((y)) == sizeof(t)) \
{t temp = ((x)); ((x)) = ((y)), ((y)) = temp;}

 /*
 * Alternatively we could use bitwise XOR for the swap, but it is considered
 * bad practice. 
 *
 * 	#define SWAP(t, x, y) if (sizeof((x)) == sizeof(t) && sizeof((y)) == sizeof(t)) \
 * 	{(x) ^= (y), (y) ^= (x), (x) ^= (y);}
*/

int main(void)
{
	int a = 6, b = 3;
	char c = 99; /* 'c' */
	float f = 42.0f ;
	long int l = 25;

	printf("int and int: types match\n");
	printf("Before SWAP\n a = %i b = %i\n", a, b);
	SWAP(int, a, b);
	printf("After  Swap\n a = %i b = %i\n", a, b);

	printf("\nchar and float: types don't match\n");
	printf("Before SWAP\n a = %c b = %2f\n", c, f);
	SWAP(int, a, b);
	printf("After  Swap\n a = %c b = %2f\n", c, f);

	printf("\nlong and int: types don't match,\
 but implicit conversion takes place\n");
	printf("Before SWAP\n a = %i b = %li\n", a, l);
	SWAP(int, a, b);
	printf("After Swap\n a = %i b = %li\n", a, l);

	return 0;
}
