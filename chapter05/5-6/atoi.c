
/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define MAXCHAR 100

/* chapter 1 */

/* atoi: convert s to integer - pointer version */
int atoi_1(char s[])
{
	int n;

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = 10 * n + (*s++ - '0');

	return n;
}

/* chater 3 */

/* atoi: convert s to integer; version 2 - pointer version */
int atoi_2(char *s)
{
	int n, sign;

	while (isspace(*s))            /* skip whitespace */
		++s;

	sign = (*s == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')     /* skip sign */
		++s;

	n = 0;
	while (isdigit(*s))
		n = 10 * n + (*s++ - '0');

	return sign * n;
}

int main(void)
{
	char string[MAXCHAR];

	printf ("Enter an integer string: ");
	scanf("%s", string);

	printf("%i\n", atoi_1(string));
	printf("%i\n", atoi_2(string));

	return 0;
}
