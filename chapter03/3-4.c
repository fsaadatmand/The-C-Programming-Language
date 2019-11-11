/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. 
 *
 * ANSWER:
 * In two's complement number representation, the limit for a signed int ranges
 * from -(2^wordsize-1) to (2^wordsize-1)-1. The most significant bit is the
 * sign bit; however, it also holds a value for negative numbers; thus, making
 * the negative limit larger than the positive limit by a value of 1. When we
 * negate the largest negative number, -(2^wordsize-1), we get a number that is
 * equal to 2^wordsize-1, which is larger than the largest positive number,
 * (2^wordsize-1)-1. This will overflow the signed int and cause unexpected
 * results. To overcome this, we can use an unsigned int for n. The check for
 * whether n is negative or not is taking care of with the assigned of n to the
 * int variable sign, in which n is convert to a signed int. 
 *
 *  By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

void itoa(unsigned, char []);
void reverse(char []);

/* itoa: convert n to characters in s */
void itoa(unsigned n, char s[])
{
	int i, sign;

	if ((sign = n) < 0) /* record sign */
		n = -n;         /* make n positive */

	i = 0;
	do {           /* generate digits in revered order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0);   /* delete it */
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
	char str[MAXLEN];

	itoa(INT_MAX, str);
	printf("%i -> %s\n", INT_MAX, str);
	itoa(INT_MIN, str);
	printf("%i -> %s\n", INT_MIN, str);

	return 0;
}
