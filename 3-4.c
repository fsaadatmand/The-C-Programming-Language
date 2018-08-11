#include <stdio.h>
#include <string.h>
#include <limits.h>

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

	if (n == INT_MIN) {           /* Add check for size */
		lastDigit = n % 10 * -1;  /* save the last digit */
		n -= 1;                   /* reduce n to fit INT_MAX */
	}

	if ((sign = n) < 0)           /* record sign */
		n = -n;

	i = 0;
	do {                 /* generate digits in reverse order */
		s[i++] = n % 10 + '0';    /* get next digit */
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	if (lastDigit > 0)
		s[0] = lastDigit + '0';

	s[i] = '\0';

	reverse(s);
}

int main(void)
{
	int intValue = -2147483648;
	char stringNumber[100];

	itoa(intValue, stringNumber);

	printf("%s\n", stringNumber);

	return 0;
}
