/*
 * Exercise 2-3. Write a function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>       /* for htoi() */ 
#include <math.h>        /* for pow() */
#include <string.h>     

#define MAXLINE 1000

/* functions */
long unsigned htoi(char []);

long unsigned htoi(char s[])
{
	int i, len;
	long unsigned intValue = 0;
	int base10;

	len = strlen(s);

	i = 0;
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
		i += 2;
		len -= 2;
	}

	for ( ; s[i] != '\0'; i++, len--) {

		if (!isxdigit(s[i]))
			return -1;

		if (isdigit(s[i])) 
			base10 = s[i] - '0';
		else if (s[i] == 'a')
			base10 = 10;
		else if (s[i] == 'b')
			base10 = 11;
		else if (s[i] == 'c')
			base10 = 12;
		else if (s[i] == 'd')
			base10 = 13;
		else if (s[i] == 'e')
			base10 = 14;
		else if (s[i] == 'f')
			base10 = 15;
		else if (s[i] == 'A')
			base10 = 10;
		else if (s[i] == 'B')
			base10 = 11;
		else if (s[i] == 'C')
			base10 = 12;
		else if (s[i] == 'D')
			base10 = 13;
		else if (s[i] == 'E')
			base10 = 14;
		else if (s[i] == 'F')
			base10 = 15;

	intValue += pow(16, len - 1) * base10;	
	}
	return intValue;
}

int main(void)
{
	unsigned long intValue;
	char xString[MAXLINE];

	printf("Enter a hexadecimal string: ");
	scanf("%s", xString);

	if ((intValue = htoi(xString)) < 0)
		printf("Invalid hexadecimal number\n");
	else
		printf("%lu\n", intValue);
	return 0;
}
