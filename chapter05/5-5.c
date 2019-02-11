/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s, t, n) copies at most n characters of t to
 * s. Full descriptions are in Appendix B.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXCHAR 32

/* strnCpy: copy at most n characters of string t to s. Returns s. Pad with
 * '\0's if t has fewer than n characters */
char *strnCpy(char *s, char *t, int n)
{
	int nChar;                     /* number of characters copied */
	int t_len;                     /* length of source string */

	t_len = strlen(t);
	nChar = 0;

	if (n <= 0)                    /* invalid inputs */
		return t;

	while (nChar < n) {            /* copy exactly n characters */
		*s++ = *t++;
		++nChar;
	}
	*s = '\0';                     /* terminate with null character */

	if (t_len < n) 
		while (nChar != n) {       /* pad t with '\0' */
			*s++ = '\0';
			++nChar;
		}
	return s - n;

}

/* strnCat: concatenate at most n characters of string t to string s, terminate
 * s with '\0'; return s*/
char *strnCat(char *s, char *t, int n)
{
	int s_len;                      /* length of s */
	int nChar = 0;

	s_len = strlen(s);
	s += s_len;                     /* find the end of s */

	while (nChar < n) {
		*s++ = *t++;
		++nChar;
	}

	*s = '\0';

	return s - s_len - nChar;
}

/* strnCmp: compare at most n characters of string s to string t; return < 0
 * if s < t, 0 if s == t, or > 0 if s > t. */
int strnCmp(char *s, char *t, int n)
{
	while (*s == *t) {
		++s;
		++t;
		--n;
		if (n == 0)
			return 0;
	}
	return *s - *t;
}

int main(void)
{
	char dest1[MAXCHAR];
	char dest2[MAXCHAR] = { "It's a " };
	char source[MAXCHAR] = { "copy me" };
	char string1[MAXCHAR] = { "compare me" };
	char string2[MAXCHAR] = { "compare me with other strings" };

	printf("%s\n", strnCpy(dest1, source, 4));
	printf("%s\n", strnCat (dest2, source, 4));
	printf("%i\n", strnCmp (string1, string2, 4));
	return 0;
}
