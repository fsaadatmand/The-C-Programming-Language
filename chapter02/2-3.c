/*
 * Exercise 2-3. Write a function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXCHAR 100

/* functions */
int htoi(char []);

int htoi(char s[])
{
	int i, isValid, hexDigit, intValue;

	i = 0;
	if (s[i] == '0') {
		++i;
		if (s[i] == 'x' || s[i] == 'X') 
			++i;
	}

	intValue = 0;
	isValid = 1;

	for ( ; isValid; ++i) {
		if (s[i] >= '0' && s[i] <= '9')
			hexDigit = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			hexDigit = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			hexDigit = s[i] - 'A' + 10;
		else 
			isValid = 0;

		if (isValid)
			intValue = 16 * intValue + hexDigit;
	}
	return intValue;
}

int main(void)
{
	int value;
	char hexString[MAXCHAR];

	printf("Enter a hexadecimal string: ");
	scanf("%s", hexString);

	value = htoi(hexString);
	printf("%i\n", value);

	return 0;
}
