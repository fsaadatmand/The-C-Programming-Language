/*
 * In two's complent number system, x &= (x - 1) deletes the right most 1-bit
 * in x. Explaing why. Use this observation to write a faster version of
 * bitcount.
 *
 * Answer: It has to do with they way binary substraction works. Substracting 1
 * from x results in inverting the rightmost bit when it is 1, leaving the
 * other bits unchanged. This essntially will produce a mask that will delete
 * the rightmost 1-bit from x when ANDed with x.  When the rightmost bit in x
 * is 0, 1 is "borrowed" from the next 1-bit on the left to perform the
 * substraction, filling any 0-bits in between with 1. This has the effect of
 * inverting the rightmost bit and the in between 0-bits from the next 1-bit.
 * The result is a mask that can be used to delete the corresponding next 1-bit
 * in x when ADDed with x, leaving the other bits unchanged..
 * By Faisal Saadatmand
 */

#include <stdio.h>

int bitcount(unsigned x);

int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= (x - 1))
			b++;
	return b;
}

int main(void)
{
	unsigned y = 255;

	printf("1-bits %i\n", bitcount(y));

	return 0;
}
