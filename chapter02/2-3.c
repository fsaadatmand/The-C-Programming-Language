/*
 * Exercise 2-3. Write a function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

/* functions */
int htoi(char []);

int htoi(char s[])
{
	int i, hexDigit, intValue;

	/* detect optional 0x or 0X prefix */
	i = 0;
	if (s[0] == '0' && tolower(s[1]) == 'x' && s[2] != '\0')
		i = 2;

	hexDigit = intValue = 0;
	for ( ; s[i] != '\0'; ++i) {
		if (!isdigit(s[i]) && (tolower(s[i]) < 'a' || tolower(s[i]) > 'f'))
			return -1; /* invalid input, exit early */
		if (isdigit(s[i]))
			hexDigit = s[i] - '0'; /* convert digits to hexadecimal*/
		else
			hexDigit = tolower(s[i]) - 'a' + 10; /* convert letters hexadecimal */
		intValue = 16 * intValue + hexDigit; /* convert hexadecimal to decimal*/
	}

	return intValue;
}

int main(void)
{
	int result;
	char s[MAXLEN];

	printf("Enter a hexadecimal string: ");
	scanf("%s", s);

	if ((result = htoi(s)) < 0)
		return -1; /* not a hexadecimal number */

	printf("%i\n", result);

	return 0;
}
