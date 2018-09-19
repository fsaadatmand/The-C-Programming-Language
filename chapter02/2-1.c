/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 * By Faisal Saadatmand
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

void computeRanges(void)
{
	/* characters */
	signed char c; 
	int maxC = 1;
	for (c = 1; c > 0; c *= 2)
		maxC *= 2;
	printf("signed char\t\t%i\t\t\t%i\n", c, maxC - 1);

	unsigned char uc;
	for (uc = -1; uc < 0; uc *= 2)
		;
	printf("unsigned char\t\t%2i\t\t\t%i\n", 0, uc);

	/* Integers */
	signed short  shrt;
	int maxShrt = 1;
	for (shrt = 1; shrt > 0; shrt *= 2)
		maxShrt *= 2;
	printf("signed short\t\t%i\t\t\t%i\n", shrt, maxShrt - 1);

	unsigned short uShrt;
	for (uShrt = -1; uShrt < 0; uShrt *= 2)
		;
	printf("unsigned short\t\t%2i\t\t\t%i\n", 0, uShrt);

	signed int sInt;
	int max_sInt = 1;
	for (sInt = 1; sInt > 0; sInt *= 2)
		max_sInt *= 2;
	printf("signed int\t\t%i\t\t%i\n", sInt, max_sInt - 1);

	unsigned int uInt;
	for (uInt = -1; uInt < 0; uInt *= 2)
		;
	printf("unsigned int\t\t%2i\t\t\t%u\n", 0, uInt);

	signed long int lInt;
	signed long int max_lInt = 1;
	for (lInt = 1; lInt > 0; lInt *= 2)
		max_lInt *= 2;
	printf("signed long\t\t%li\t%li\n", lInt, max_lInt - 1);

	unsigned long int ulInt;
	for (ulInt = -1; ulInt < 0; ulInt *= 2)
		;
	printf("unsigned long\t\t%2i\t\t\t%lu\n", 0, ulInt);

	signed long long llInt;
	signed long long max_llInt = 1;
	for (llInt = 1; llInt > 0; llInt *= 2)
		max_llInt *= 2;
	printf("signed long long\t%lli\t%lli\n", llInt, max_llInt - 1);

	unsigned long long   ullInt;
	for (ullInt = -1; ullInt < 0; ullInt *= 2)
		;
	printf("unsigned long long\t%2i\t\t\t%llu\n", 0, ullInt);

	printf("\n");

	/* floating points */
	/* see IEEE 754 standards */
	float fltMin;
	float fltMax;
	fltMin = (2 - pow(2, -23)) / pow(2, 127);
	fltMax = (2 - pow(2, -23)) * pow(2, 127);
	printf("float\t\t\t%g\t\t%g\n", fltMin, fltMax);

	double dblMin;
	double dblMax;
	dblMin = (2 - pow(2, -52)) / pow(2, 1023);
	dblMax = (2 - pow(2, -52)) * pow(2, 1023);
	printf("double\t\t\t%lg\t\t%lg\n", dblMin, dblMax);

}

void stdLibraryRanges(void)
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
	printf("\t**** Computed Ranges *****\n");
	computeRanges();

	printf("\n\t**** Library function Ranges *****\n");
	stdLibraryRanges();

	return 0;
}
