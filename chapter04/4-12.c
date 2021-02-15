/*
 * Exercise 4-12: Adapt the idea of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 *
 * By Faisal Saadatmand
 */

/*
 * NOTE: We could have made i a static variable; however, that is problematic
 * because its value will persists throughout the entire life of the program, and
 * thus, multiple calls to itoar will use the value of i from the previous call,
 * which will result in an undesirable outcome.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 1000

/* functions */
void itoa(int, char []);
int itoar(int, char [], int);

/* itoa: interface function to itoar */
void itoa(int n, char s[])
{
	itoar(n, s, 0);
}

/* itoar: convert n to characters in s, recursive version */
int itoar(int n, char s[], int i)
{
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10)
		i = itoar(n / 10, s, i); /* recursive call */
	s[i++] = n % 10 + '0';
	s[i] = '\0';
	return i; /* return the updated value of i */
}

int main(void)
{
	char str[MAXLEN];

	itoa(996, str);
	printf("%s\n", str);

	itoa(-2345, str);
	printf("%s\n", str);

	itoa(INT_MAX, str);
	printf("%s\n", str);

	itoa(INT_MIN, str);
	printf("%s\n", str);

	return 0;
} 
