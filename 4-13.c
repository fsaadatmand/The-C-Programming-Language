/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[]);

/* reverse function: reverse string s in place, recursive version */
void reverse(char s[])
{
	int c, j;
	static int i;

	j = (strlen(s) - 1) - i;
	if (j >= 0) {
		c = s[i];
		s[i++] = s[j];
		s[j] = c;
		reverse(s);
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
