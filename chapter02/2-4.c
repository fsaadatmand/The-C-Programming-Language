/*
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXCHAR 1000

/* functions */
void squeeze(char [], char []);

void squeeze(char s1[], char s2[])
{
	int i, j, k;

	k = 0;
	for (i = 0; s1[i] != '\0'; ++i) {
		for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; ++j)
			;
		if (s2[j] == '\0') /* match not found */
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
}

int main(void)
{
	char string1[MAXCHAR] = { "clean* *this- *str*-ing *** ---" };
	char string2[MAXCHAR] = { "*-" };

	squeeze(string1, string2);
	printf("%s\n", string1);

	return 0;
}
