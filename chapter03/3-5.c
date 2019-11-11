/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s.
 *
 * By Faisal Saadatmand
 */

#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

/* functions */
void reverse(char []);
void itob(unsigned, char [], int);

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itob: converts the integer n into a base b character representation in the
 * string s. */
void itob(unsigned n, char s[], int b)
{
	int i, sign, digit;
	const char baseDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
								  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	if (b == 10 && (sign = n) < 0)
		n = -n; /* or you can use ~n + 1 */

	i = 0;
	do {        /* generate digits in reverse order */
		digit = n % b; /* get next digit */
		s[i++] = baseDigits[digit];
	} while ((n /= b) > 0);

	if (b == 10 && sign < 0) /* add sign symbol for base 10 */
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);
}

int main(void)
{
	int i;
	char str[MAXLEN];

	printf("converting %i and %i to\n", INT_MIN, INT_MAX);
	for (i = 2; i <= 16; ++i) {
		printf("Base% i:\n", i);
		itob(INT_MIN, str, i);
		printf(" %s\n",  str);
		itob(INT_MAX, str, i);
		printf(" %s\n", str);
	}

	return 0;
}
