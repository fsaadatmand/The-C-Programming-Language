/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. 
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[]);

/* reverse function: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j --) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign, lastDigit;

	lastDigit = 0;
	if (n == INT_MIN) {                   /* add check for size */
		lastDigit = (n % 10 * -1) + '0';  /* extract save the last digit */
		n -= 1;                           /* reduce n to fit INT_MAX */
	}

	if ((sign = n) < 0)                   /* record sign */
		n = -n;

	i = 0;
	do {                                  /* generate digits in reverse order */
		s[i++] = n % 10 + '0';            /* get next digit */
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	if (lastDigit > 0)                    /* put back saved last digit */
		s[0] = lastDigit;

	s[i] = '\0';

	reverse(s);
}

int main(void)
{
	int intValue;
	char stringNumber[64];

	printf("Enter integer to convert to a string: ");
	scanf("%i", &intValue);

	itoa(intValue, stringNumber);

	printf("%s\n", stringNumber);

	return 0;
}
