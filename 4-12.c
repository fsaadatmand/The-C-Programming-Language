/*
 * Exercise 4-12: Adapt the idea of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int sign, lastDigit;
	int static i;                         /* note static type */

	lastDigit = 0;
	if (n == INT_MIN) {                   /* add check for minimum signed int */
		lastDigit = (n % 10 * -1) + '0';  /* extract and save the last digit */
		n += 1;                           /* reduce n to fit into INT_MAX */
	}

	if (n < 0) {
		s[i++] = '-';                     /* store leading negative sign */
		n = -n;
	}

	if (n / 10)
		itoa(n / 10, s);                  /* recursive call */

	s[i++] = n % 10 + '0';

	if (lastDigit > 0) {
		--i;
		s[i++] = lastDigit;               /* put back saved last digit */
	}

	s[i] = '\0';
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
