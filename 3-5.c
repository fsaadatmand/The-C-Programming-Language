#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void reverse(char s[]);
int towsComplement(int number);
void itoab(int number, char convertedNumber[], int base);

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

/* towsComplement: converts a number to its two's complement value in decimal */
int towsComplement(int number)
{
	unsigned int i, nextDigit, result;
	int binaryValue[64];

	number += 1;
	number = -number;

	i = 0;
	do {                           /* convert to binary */
		nextDigit = number % 2;	
		binaryValue[i] = ~nextDigit;
		number /= 2;
		++i;
	} while (number != 0);

	result = 0;
	for (--i; i >= 0; --i)
		result += binaryValue[i] * pow(2, i);
	printf("%f\n", result);
	
	return result;
}

/* itoab: convert number into a base base character representation in the string  s */
void itoab(int number, char convertedNumber[], int base)
{

	int i, sign, lastDigit = 0, nextDigit;
	unsigned int negativeNumber;
	const char baseDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
		                          '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	if (number == INT_MIN) {           /* check for size */
		lastDigit = number % base * -1;  /* save the last digit */
		number -= 1;                   /* reduce number to fit INT_MAX */
	}

	if ((sign = number) < 0)           /* record sign */
		if (base == 10)
			number = -number;
		else {                /* two's complement */
		//	number = towsComplement(number);
		printf("%x\n", number);
		}

	//	printf("%i\n", number);


	i = 0;
	do {                 /* generate digits in reverse order */
		nextDigit = number % base;    /* get next digit */
		number /= base;
		convertedNumber[i] = baseDigits[nextDigit];
		++i;
	} while (number != 0);

	if (sign < 0 && base == 10)
		convertedNumber[i++] = '-';

	if (lastDigit > 0)
		convertedNumber[0] = lastDigit + '0';

	convertedNumber[i] = '\0';

	reverse(convertedNumber);
}

int main(void)
{
	char stringNumber[64];

	itoab(-1, stringNumber, 16);

	return 0;
}
