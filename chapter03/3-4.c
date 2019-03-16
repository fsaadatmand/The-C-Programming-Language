/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. 
 *
 * Answer: In two's complement number representation, the limit ranges from
 * -(2^wordsize-1) to (2^wordsize-1)-1. The most significant bit is the sign
 *  bit; however, it also holds a value for negative numbers; thus, making the
 *  negative limit larger than the positive limit by a value of 1. This makes a
 *  binary value of -(2^wordsize-1) equal to 2^wordsize-1, which is larger than
 *  (2^wordsize-1)-1. For example, in a 8-bit wordsize, -128 and 128 are
 *  represented as 0x80, which is larger than what the largest positive number
 *  an 8-bit word can hold, 127 or 0x8f.  The itoa function's first assignment
 *  instruction is to negate n. In the case n is
 * -(2^worldsize-1), the negation will produce the same binary number, and
 *  therefore, the algorithm will fails at the do/while loop.  
 *
 *  By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 100

void itoa(int, char []);
void reverse(char []);

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	i = 0;
	if ((sign = n) < 0) {
		s[i++] = -(n % 10) + '0';   /* extract last digit */
		n /= 10;                    /* reduce value to fit signed int */
		n = -n;                     /* negate value */ 
	}

	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int main(void)
{
	char string[MAXLEN];
	int intValue;

	printf("Enter an integer to convert in a string (range: %i to %i):\n",
			INT_MIN, INT_MAX);
	scanf("%i", &intValue);
	itoa(intValue, string);
	printf("%s\n", string);

	return 0;
}
