/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to right by n positions.
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
unsigned int rightrot(unsigned int, int);

unsigned int rightrot(unsigned int x, int n)
{
	int size;
	unsigned int bits = 0;
	unsigned int rotatedX = 0;
	
	size = (sizeof(unsigned int)) * 8;    /* never assume size of int */

	bits = x & ~(~0 << n);                /* extract n bits to be rotated */
	rotatedX = (x >> n) | bits << (size - n);

	return rotatedX;
}

int main(void)
{
	unsigned int x = 0XAF14E5CB;
	int          n = 16;

	printf("%x\n", rightrot(x, n));

	return 0;
}
