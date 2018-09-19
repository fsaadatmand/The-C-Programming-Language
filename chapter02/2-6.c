/* 
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged.
 * by Faisal Saadatmand
 * */

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned y);

unsigned int setbits(unsigned int x, int p, int n, unsigned y)
{
	unsigned mask = ~(~0 << n);    /* mask to extract n bits from y */
	unsigned xORy;

	xORy = x | (y & mask) << p;   /* move bits to p, OR with x to set them */
	return xORy;
}

int main(void)
{
	unsigned int x = 0XF8FF;
	unsigned int y = 0XF0A2;
	int p = 8;                   /* starting postion of bits */
	int n = 2;                   /* number of bits to set */

	printf("%x\n", setbits(x, p, n, y)); 
	return 0;
}
