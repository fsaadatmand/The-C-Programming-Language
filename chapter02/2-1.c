/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 *
 * For signed variables:
 * largest negative number is -(2^nbits-1)
 * largest positive number is (2^nbits-1)-1
 *
 * The loop iterates until the variable overflows the positive limit by 1. In
 * binary (two's complement), this results in achieving the largest negative
 * number with the loop's index and the max number with the result of the
 * calculation inside the loop minus 1. Note: we can also achieve the largest
 * positive number by negating the loop index and subtract one from it.
 * However; the cost of one extra variable (long long max), we gain in code
 * clarity.
 *
 * For unsigned variables:
 * min is 0
 * max (2^nbits)-1
 *
 * We do the same for the loop but we iterate the other way: we start from -1 all
 * the way up to 0.
 *
 * for floating point types:
 * refer to IEEE 754 standards
 *
 * By Faisal Saadatmand
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* functions */
void computeRanges(void);
void stdLibraryMacros(void);

void computeRanges(void)
{
	long long unsigned int max;

	/* characters */
	signed char c;

	for (c = max = 1; c > 0; c *= 2)
		max *= 2;
	printf("signed char\t\t%i\t\t\t%llu\n", c, max - 1);

	unsigned char uc;

	for (uc = -1; uc < 0; uc *= 2)
		max *= 2; 
	printf("unsigned char\t\t%2i\t\t\t%u\n", 0, uc);

	/* Integers */
	signed short  shrt;

	for (shrt = max = 1; shrt > 0; shrt *= 2)
		max *= 2;
	printf("signed short\t\t%i\t\t\t%llu\n", shrt, max - 1);

	unsigned short uShrt;

	for (uShrt = -1; uShrt < 0; uShrt *= 2)
		max += uShrt;
	printf("unsigned short\t\t%2i\t\t\t%u\n", 0, uShrt);

	signed int i;

	for (i = max = 1; i > 0; i *= 2)
		max *= 2;
	printf("signed int\t\t%i\t\t%llu\n", i, max - 1);

	unsigned int ui;

	for (ui = -1; ui < 0; ui *= 2)
		;
	printf("unsigned int\t\t%2u\t\t\t%u\n", 0, ui);

	signed long int li;

	for (li = max = 1; li > 0; li *= 2)
		max *= 2;
	printf("signed long\t\t%li\t%llu\n", li, max - 1);

	unsigned long int uli;

	for (uli = -1; uli < 0; uli *= 2)
		;
	printf("unsigned long\t\t%2u\t\t\t%lu\n", 0, uli);

	signed long long lli;

	for (lli = max = 1; lli > 0; lli *= 2)
		max *= 2;
	printf("signed long long\t%lli\t%llu\n", lli, max - 1);

	unsigned long long   ulli;
	for (ulli =  -1; ulli < 0; ulli *= 2)
		;
	printf("unsigned long long\t%2i\t\t\t%llu\n", 0, ulli);

	printf("\n");

	/* floating points */
	/* see IEEE 754 standards */
	float fltMin, fltMax;
	double dblMin, dblMax, mantissa, exponent;
	
	mantissa = 1.0;
	exponent = 1.0;
	for (i = 0; i < 23; ++i)
		 mantissa /= 2;
	for (i = 0; i < 127; ++i)
		exponent *= 2;
	fltMin = (2 - mantissa) / exponent;
	fltMax = (2 - mantissa) * exponent;
	printf("float\t\t\t%g\t\t%g\n", fltMin, fltMax);

	mantissa = 1.0;
	for (i = 0; i < 52; ++i)
		mantissa /= 2;
	exponent = pow(2, 1023);    /* too big to fit into a variable */
	dblMin = (2 - mantissa) / exponent;
	dblMax = (2 - mantissa) * exponent;
	printf("double\t\t\t%g\t\t%g\n", dblMin, dblMax);
}

void stdLibraryRanges()
{
	/* Characters and Integers */
	printf("signed char\t\t%.0f\t\t\t%.0f\n",
			pow(2, (sizeof(char) * 8 - 1)) * -1,
			pow(2, (sizeof(char) * 8) - 1) - 1);
	printf("unsigned char\t\t%2i\t\t\t%.0f\n", 0,
			pow(2, sizeof(unsigned char) * 8) - 1);

	printf("signed short\t\t%.0f\t\t\t%.0f\n",
			pow(2, (sizeof(short) * 8 - 1)) * -1,
			pow(2, (sizeof(short) * 8) - 1) - 1);
	printf("unsigned short\t\t%2i\t\t\t%0.f\n", 0,
			pow(2, sizeof(unsigned short) * 8) - 1);

	printf("signed int\t\t%.0f\t\t%.0f\n",
			pow(2, (sizeof(int) * 8 - 1)) * -1,
			pow(2, (sizeof(int) * 8) - 1) - 1);
	printf("unsigned int\t\t%2i\t\t\t%0.f\n", 0,
			pow(2, sizeof(unsigned int) * 8) - 1);

	printf("signed long\t\t%.0f\t%.0Lf\n",
			pow(2, (sizeof(long) * 8 - 1)) * -1,
			(long double) pow(2, (sizeof(long) * 8) - 1) - 1);
	printf("unsigned long\t\t%2i\t\t\t%0.Lf\n", 0,
			(long double)  pow(2, sizeof(unsigned long) * 8) - 1);

	printf("signed long\t\t%.0f\t%.0Lf\n",
			pow(2, (sizeof(long long) * 8 - 1)) * -1,
			(long double) pow(2, (sizeof(long long) * 8) - 1) - 1);
	printf("unsigned long\t\t%2i\t\t\t%0.Lf\n", 0,
			(long double) pow(2, sizeof(unsigned long long) * 8) - 1);

	printf("\n");

	/* floating points */
	/* see IEEE 754 standards */
	printf("float\t\t\t%g\t\t%g\n",
			(2 - pow(2, -23)) / pow(2, 127),(2 - pow(2, -23)) * pow(2, 127));
	printf("double\t\t\t%lg\t\t%lg\n",
			(2 - pow(2, -52)) / pow(2, 1023), (2 - pow(2, -52)) * pow(2, 1023));
}
void stdLibraryMacros(void)
{
	/* characters */
	printf("signed char\t\t%i\t\t\t%i\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char\t\t%2i\t\t\t%u\n", 0, UCHAR_MAX);
	/* integers */
	printf("signed short\t\t%i\t\t\t%i\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short\t\t%2i\t\t\t%u\n", 0, USHRT_MAX);
	printf("signed int\t\t%i\t\t%i\n", INT_MIN, INT_MAX);
	printf("unsigned int\t\t%2i\t\t\t%u\n", 0, UINT_MAX);
	printf("signed long\t\t%li\t%li\n", LONG_MIN, LONG_MAX);
	printf("unsigned long\t\t%2i\t\t\t%lu\n", 0, ULONG_MAX);
	printf("signed long long\t%lli\t%lli\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long\t%2i\t\t\t%llu\n", 0, ULLONG_MAX);

	printf("\n");

	/* floating points */
	printf("float\t\t\t%g\t\t%g\n", FLT_MIN, FLT_MAX);
	printf("double\t\t\t%lg\t\t%lg\n", DBL_MIN, DBL_MAX);
	printf("long double\t\t%Lg\t\t%Lg\n", LDBL_MIN, LDBL_MAX);
}

int main(void)
{
	printf("\t**** Computed Manually *****\n");
	computeRanges();

	printf("\n\t**** Computed Using Library functions *****\n");
	stdLibraryRanges();

	printf("\n\t**** Printed Using Library Macros in limits.h *****\n");
	stdLibraryMacros();

	return 0;
}
