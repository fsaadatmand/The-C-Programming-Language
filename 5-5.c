/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s, t, n) copies at most n characters of t to
 * s. Full descriptions are in Appendix B.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

/* strnCpy: copy at most n characters of string t to s. Returns s. Pad with
 * '\0's if t has fewer than n characters */
char *strnCpy(char *s, char *t, int n)
{
	int s_len, t_len;

	s_len = strlen(s);
	t_len = 0;

	if (n <= 0)                    /* invalid inputs */
		return s;

	while (t_len < n) {            /* copy exactly n characters */
		*t++ = *s++;
		++t_len;
	}
	*t = '\0';                     /* terminate with null character */

	if (s_len < n) 
		while (t_len != n) {       /* pad t with '\0' */
			*t++ = '\0';
			++t_len;
		}

	return t - n;

}

int main(void)
{
	char string1[32] = { "copy me" };
	char string2[32];

	printf("%s\n", strnCpy(string1, string2, 4));
	
	return 0;
}
