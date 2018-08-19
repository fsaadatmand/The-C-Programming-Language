#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itob(int number, char convertedNumber[], int base);

/* reverse function: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j --) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		--j;
	}
}

/* itob: convert number into a base base character representation in the string  s */
void itob(int number, char convertedNumber[], int base)
{
	int i, sign;
	unsigned int uNumber, nextDigit;
	const char baseDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
		                          '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	sign = 0;
	if (number < 0)                  /* record sign */
		sign = 1;

	uNumber = (unsigned) number;     /* work in two's complement number system */

	if (sign > 0 && base == 10)      /* convert back to decimal for base 10 */
		uNumber = ~uNumber + 1;

	i = 0;
	do {                             /* generate digits in reverse order */
		nextDigit = uNumber % base;  /* get next digit */
		uNumber /= base;
		convertedNumber[i] = baseDigits[nextDigit];
		++i;
	} while (uNumber != 0);

	if (sign > 0 && base == 10)      /* add sign symbol for base 10 */
		convertedNumber[i++] = '-';

	convertedNumber[i] = '\0';

	reverse(convertedNumber);
}

int main(void)
{
	int number, base;
	char stringNumber[64];

	printf("Enter an integer to convert: ");
	scanf("%i", &number); 

	printf("Enter base: ");
	scanf("%i", &base);

	itob(number, stringNumber, base);
	
	printf("%s\n", stringNumber);

	return 0;
}
