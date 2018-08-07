/* 
 * function that returns x with the n bits that begin at position p inverted
 * leaving the other bits unchanged.
 * by Faisal Saadatmand
 * */

#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

unsigned int invert(unsigned int x, int p, int n)
{
	unsigned mask;
	unsigned invertedBits;
	
	mask = ~(x & ~(~0 << n) << p);
	invertedBits = x & mask;

	 return invertedBits;
}

int main(void)
{
	unsigned int x = 0XFFFF;
	int p = 4;                   /* starting postion of bits */
	int n = 4;                   /* number of bits to set */

	printf("%x\n", invert(x, p, n)); 

	return 0;
}
