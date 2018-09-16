/* A program that computes and prints value rages for all the variable types */

#include <stdio.h>
#include <limits.h>
#include <float.h>

void computeRanges(void)
{
	signed char          sChar;
	unsigned char        uChar;
	signed short         shrtInt;
	unsigned short       uShrtInt;
	signed int           sInt;
	unsigned int         uInt;
	signed long          lInt;
	unsigned long        uLInt;
	signed long long     lLInt;
	unsigned long long   uLLInt;
	long                 maxValue;
	long                 minValue;

	maxValue = 1;
	for (sChar = 1; sChar > 0; sChar *= 2)
		maxValue *= 2;
	for (sChar = -1; sChar < 0; sChar *= 2)
		minValue = sChar;
	printf("signed char\t%i\t\t\t%i\n", minValue, maxValue - 1);

	maxValue = 1;
	for (uChar = 1; uChar > 0; uChar *= 2)
		maxValue *= 2;
	printf("unsigned char\t%2i\t\t\t%u\n", 0, maxValue - 1);

	maxValue = 1;
	for (shrtInt = 1; shrtInt > 0; shrtInt *= 2)
		maxValue *= 2;
	for (shrtInt = -1; shrtInt < 0; shrtInt *= 2)
		minValue = shrtInt;
	printf("signed short\t%i\t\t\t%i\n", minValue, maxValue - 1);

	maxValue = 1;
	for (uShrtInt = 1; uShrtInt > 0; uShrtInt *= 2)
		maxValue *= 2;
		minValue = shrtInt;
	printf("unsigned short\t%2i\t\t\t%u\n", 0, maxValue - 1);

	maxValue = 1;
	for (sInt = 1; sInt > 0; sInt *= 2)
		maxValue *= 2;
	for (sInt = -1; sInt < 0; sInt *= 2)
		minValue = sInt;
	printf("signed int\t%i\t\t%i\n", minValue, maxValue - 1);

	maxValue = 1;
	for (uInt = 1; uInt > 0; uInt *= 2)
		maxValue *= 2;
	printf("unsigned int\t%2i\t\t\t%u\n", 0, maxValue - 1);

	maxValue = 1;
	for (lInt = 1; lInt > 0; lInt *= 2)
		maxValue *= 2;
	for (lInt = -1; lInt < 0; lInt *= 2)
		minValue = lInt;
	printf("signed long\t%li\t%li\n", minValue, maxValue - 1);

	maxValue = 1;
	for (uLInt = 1; uLInt > 0; uLInt *= 2)
		maxValue *= 2;
	printf("unsigned long\t%2i\t\t\t%lu\n", 0, maxValue - 1);

	maxValue = 1;
	for (lLInt = 1; lLInt > 0; lLInt *= 2)
		maxValue *= 2;
	for (lLInt = -1; lLInt < 0; lLInt *= 2)
		minValue = lLInt;
	printf("signed long long\t%lli\t%lli\n", minValue, maxValue - 1);

	maxValue = 1;
	for (uLLInt = 1; uLLInt > 0; uLLInt *= 2)
		maxValue *= 2;
	printf("unsigned long long\t%2i\t\t\t%llu\n", 0, maxValue - 1);
}

void stdLibraryRanges(void)
{
	printf("signed char\t\t%i\t%i\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char\t\t%2i\t%u\n", 0, UCHAR_MAX);
	printf("signed short\t\t%i\t%i\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short\t\t%2i\t%u\n", 0, USHRT_MAX);
	printf("signed int\t\t%i\t%i\n", INT_MIN, INT_MAX);
	printf("unsigned int\t\t%2i\t%u\n", 0, UINT_MAX);
	printf("signed long\t\t%li\t%li\n", LONG_MIN, LONG_MAX);
	printf("unsigned long\t\t%2i\t%lu\n", 0, ULONG_MAX);
	printf("signed long long\t%lli\t%lli\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long\t%2i\t%llu\n", 0, ULLONG_MAX);

	printf("\n");
	printf("float\t\t%f\t%g\n", FLT_MIN, FLT_MAX);
	printf("double\t\t%lf\t%lg\n", DBL_MIN, DBL_MAX);
	printf("long double\t%llf\t%llg\n", LDBL_MIN, LDBL_MAX);
}

int main(void)
{
	printf("\t**** Computed Ranges *****\n");
	computeRanges();

	printf("\n\t**** Library function Ranges *****\n");
	stdLibraryRanges();

	printf("Size of in %d bytes\n", sizeof(int));
	return 0;
}
