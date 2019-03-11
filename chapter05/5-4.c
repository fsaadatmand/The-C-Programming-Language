/*
 * Exercise 5-4. Write the function strend(s, t), which returns 1 if string t
 * occurs at the end of the string s, and zero otherwise.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

/* functions */
int strend(char *, char *);

/* strend: returns 1 if t occurs at the end of s, and zero otherwise */
int strend(char *s, char *t)
{
	unsigned slen, tlen;

	if ((slen = strlen(s)) >= (tlen = strlen(t)))  /* check s's boundaries */
		for (s += slen - tlen; *s == *t; s++, t++)
			if (*s == '\0')
				return 1;              /* ends match */
	return 0;
}

int main(void)
{
	char string1[] = { "this is a string" };
	char string2[] = { "string" };

	printf("%i\n", strend(string1, string2));
	
	return 0;
}
