/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
void strCat(char *, char *);

/* concatenate t to end of s; s must be big enough */
void strCat(char *s, char *t)
{
  while (s && *s) /* find end of s */
	  ++s;
  while (s && t && (*s++ = *t++)) /* copy t */
    ;
}

int main(void)
{
	char str1[64] = { "conca" };
	char str2[] = { "tonate" };

	strCat(str1, str2);
	printf("%s\n", str1);

	return 0;
}
