/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount.
 *
 * By Faisal Saadatmand
 */

/*
 * ANSWER:
 *
 * It has to do with the way binary subtraction works in two's complement
 * number system, which is similar to base 10 subtraction.
 *
 * The bits are subtracted from each other starting from the least to the most
 * significant bit:
 * 
 * 		0xFF - 0x01 = 0xFE 
 *
 * 		Or
 *
 * 		1111 1111 - 0000 0001 = 1111 1110
 *
 * However, we cannot subtract a higher binary number from a lesser one, i.e.
 * subtracting 1 from 0. In this case, we "borrow" 1 from the next available
 * 1-bit to left (from the rightmost 1-bit). We then add 2 or 10b (base^n) to
 * the binary number we were trying to subtract from. This has the effect of
 * turning off the next available 1-bit and turning on any 0-bits after it. In
 * other words, all the bits starting with the rightmost 1-bit will be
 * inverted:
 *
 * 		0xF8 - 0x01 =  0xF7
 *
 * 		or
 *
 * 		1111 1000 - 0000 0001 = 11111  0111
 *
 * Notice the 4 least significant bits are inverted.
 *
 * The result of the subtraction, then, produces a mask that when ANDed with
 * the original value x will turn off the rightmost 1-bit, leaving the other
 * bits unchanged.
 *
 * Given this observation, we can use x &= (x - 1) instead of x >>= 1 as the
 * increment expression in the for loop. This would allow us to omit the test
 * for the least significant bit inside the loop.
 */

#include <stdio.h>

/* functions */
int bitcount(unsigned);

int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= (x - 1))
			++b;
	return b;
}

int main(void)
{
	unsigned y = 0x2;

	printf("%i 1-bit(s)\n", bitcount(y));

	return 0;
}
