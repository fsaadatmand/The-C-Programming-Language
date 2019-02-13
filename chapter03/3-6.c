/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left is necessary to make it wide enough.
 * By Faisal Saadatmand
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

/* functions */
void reverse(char []);
void itoa(int, char [], int);

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
void itoa(int n, char s[], int w)
{
	int i, sign, lastDigit, padLeft;

	sign = lastDigit = padLeft = 0;

	if (n == INT_MIN) {                   /* add check for size */
		lastDigit = (n % 10 * -1) + '0';  /* extract and save the last digit */
		n -= 1;                           /* reduce n to fit INT_MAX */
	}

	if ((sign = n) < 0)                   /* record sign */
		n = -n;

		i = 0;
	do {                                  /* generate digits in reverse order */
		s[i++] = n % 10 + '0';            /* get next digit */
	} while ((n /= 10) > 0);

	padLeft = w - i % w;                  /* pad n digits to the left */
	if (padLeft != w)
		while (padLeft > 0) {
			s[i++] = '0';
			--padLeft;
		}

	if (sign < 0)
		s[i++] = '-';

	if (lastDigit > 0)
		s[0] = lastDigit;                 /* put back saved last digit */

	s[i] = '\0';

	reverse(s);
}

int main(void)
{
	int intValue, width;
	char stringNumber[64];

	printf("Enter integer to convert to a string: ");
	scanf("%i", &intValue);

	printf("Enter padding width: ");
	scanf("%i", &width);

	itoa(intValue, stringNumber, width);

	printf("%s\n", stringNumber);

	return 0;
}
