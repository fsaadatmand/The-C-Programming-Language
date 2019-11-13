/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s, t, n) copies at most n characters of t to
 * s. Full descriptions are in Appendix B.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXCHAR 32

/* functions */
char *strnCpy(char *, char *, const size_t);
char *strnCat(char *, char *, const size_t);
int strnCmp(const char *, const char *, const size_t);

/* strnCpy: copy at most n characters of string t to s. Returns s. Pad with
 * '\0's if t has fewer than n characters */
char *strnCpy(char *s, char *t, const size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
		if (!(*s++ = *t++)) /* copy the character */
			*s = '\0'; /* pad with '\0's, if t's length is < n */
	*s = '\0'; /* add the terminating character */

	return s - n;
}

/* strnCat: concatenate at most n characters of string t to string s, terminate
 * s with '\0'; return s */
char *strnCat(char *s, char *t, const size_t n)
{
	size_t i, s_len, t_len, lim;

	s += (s_len = strlen(s)); /* advance pointer */
	lim = (n > (t_len = strlen(t))) ? t_len : n; /* scale down n */
	for (i = 0; i < lim && (*s++ = *t++); ++i)
		;
	*s = '\0';
	return s - s_len - i;
}

/* strnCmp: compare at most n characters of string s to string t; return < 0
 * if s < t, 0 if s == t, or > 0 if s > t. */
int strnCmp(const char *s, const char *t, const size_t n)
{
	size_t i; 

	for (i = 1; i < n && *s == *t; ++s, ++t, ++i)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

int main(void)
{
	char dest[MAXCHAR];

	printf("%s\n", strnCpy(dest, "copy me", 4));
	printf("%s\n", strnCat(dest, "concatenate", 4));
	printf("%i\n", strnCmp ("samee", "same", 4));
	printf("%i\n", strnCmp ("samee", "same", 5));

	return 0;
}
