/*
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXCHAR 100

void squeeze(char s1[], char s2[]);

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	int match = 0;

	i = j = k = 0;
	for (i = 0; s1[i] != '\0'; ++i) {
		for (j = 0; match != 1 && s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				match = 1;
		if (!match)
			s1[k++] = s1[i];
		match = 0;
	}
	s1[k] = '\0';
}

int main(void)
{
	char string1[MAXCHAR] = { "*from *this- *str*-ing *** ---" };
	char string2[MAXCHAR] = { "*-" };

	squeeze(string1, string2);

	printf("%s\n", string1);

	return 0;
}
