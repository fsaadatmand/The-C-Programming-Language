/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

/* atof from exercise 4-2. */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof: convert string s to doube */
double atof(char *s)
{
	int    sign, expSign;
	double val, power, exponent;

	while (isspace(*s))                         /* skip whitespace */
		++s;

	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		++s;
	
	for (val = 0.0; isdigit(*s); ++s)
		val = 10.0 * val + (*s - '0');
	
	if (*s == '.')
		++s;

	for (power = 1.0; isdigit(*s); ++s) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}

	if (*s != '\0') {                           /* handle scientific notation */
		if (*s == 'e' || *s == 'E')
			++s;
		else
			return -1;

		expSign = (*s == '-') ? -1 : 1;         /* record the exponent sign */
		if (*s == '+' || *s == '-')
			++s;

		for (exponent = 0.0; isdigit(*s); ++s)  /* extract the exponent */
			exponent = 10.0 * exponent + (*s - '0');

		return (sign * val / power) * pow(10, expSign * exponent);

	} else
		return sign * val / power;
}

int main(void)
{
	char number[64]  = { "123.45" };
	char number2[64] = { "123.45e-6" };
	char number3[64] = { "123.45e+6" };

	printf("%f\n", atof(number));
	printf("%f\n", atof(number2));
	printf("%f\n", atof(number3));

	return 0;
}
