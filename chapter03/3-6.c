/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough.
 *
 * By Faisal Saadatmand
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

/* functions */
void reverse(char []);
void itoa(unsigned, char [], int);

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
void itoa(unsigned n, char s[], int w)
{
	int i, sign, nChar; 

	if ((sign = n) < 0) /* record sign */
		n = -n;         /* make n positive */

	i = 0;
	do {     /* generate digits in revered order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0);   /* delete it */

	if (sign < 0)
		s[i++] = '-';

	/* left padding */
	for (nChar =  w - (i % w); nChar > 0; --nChar)
		s[i++] = ' ';
	s[i] = '\0';

	reverse(s);
}

int main(void)
{
	int intValue, width;
	char str[MAXLEN];

	printf("Enter integer to convert to a string: ");
	scanf("%i", &intValue);

	printf("Enter minimum field width: ");
	scanf("%i", &width);

	itoa(intValue, str, width);

	printf("%s\n", str);

	return 0;
}
