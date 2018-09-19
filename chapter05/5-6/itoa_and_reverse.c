/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

/*
 * chapter 3
 */

/* reverse function: reverse string s in place */
void reverse(char *s)
{
	int c;
	char *t;

	t = s;                   /* point to what s points to */           
	t += (strlen(s) - 1);    /* point to the end of s */

	while (s < t) {          /* swap characters */
		c = *s;
		*s++ = *t;
		*t-- = c;
	}
}

/* itoa: convert n to characters in s */
void *itoa_1(int n, char *s)
{
	int sign, nChar;

	if ((sign = n) < 0)     /* record sign */
		n = -n;

	nChar = 0;
	do {
		*s++ = n % 10 + '0';
		++nChar;
	} while ((n /= 10) > 0);

	if (sign < 0) {
		*s++ = '-';
		++nChar;
	}

	*s = '\0';

	reverse(s - nChar);
}

int main(void)
{
	char string[MAXCHAR];
	int intValue;

	printf ("Enter an integer string: ");
	scanf("%i", &intValue);

	itoa_1(intValue, string);
	printf("%s\n", string);

	return 0;
}
