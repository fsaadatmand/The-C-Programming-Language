/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. 
 *
 *  By Faisal Saadatmand
 */

/*
 * ANSWER:
 * In two's complement number representation, the range of values an int can
 * hold is from -(2^wordsize-1) to (2^wordsize-1)-1. The most significant bit
 * is the sign bit; however, it also holds a value for negative numbers; thus,
 * making the negative limit larger than the positive limit by a value of 1.
 * When we negate the largest negative number, -(2^wordsize-1), we get a number
 * that is equal to 2^wordsize-1, which is larger than the largest positive
 * number, (2^wordsize-1)-1. This will overflow a signed int and cause
 * unexpected results. To overcome this, we can use an unsigned int for n. The
 * check for whether n is negative or not is taking care of with the assigned
 * of n to the int variable sign, in which n is convert to a signed int.
 *
 * Alternatively, we could avoid negating n altogether and use the abs function
 * from stdlib.h to extract the digits. See 3-4a.c.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include<conio.h>
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
	} while ((n /= 10) != 0);   /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse the order of the characters in the string s */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int main(void)
{
	char str[MAXLEN];

	itoa(0, str); /* do-while loop is necessary for 0 */
	printf("%i -> %s\n", 0, str);
	itoa(INT_MAX, str);
	printf("%i -> %s\n", INT_MAX, str);
	itoa(INT_MIN, str);
	printf("%i -> %s\n", INT_MIN, str);

	return 0;
}
