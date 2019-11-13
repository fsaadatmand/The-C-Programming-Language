/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

/* functions */
void reverse(char []);

/* reverse function: reverse string s in place, recursive version */
void reverse(char s[])
{
	int c;
	static unsigned long i = 0, j = 0;
	
	if (j < strlen(s) - 1) {
		++j;
		reverse(s);
	}
	if (i < j) {
		c = s[i];
		s[i++] = s[j];
		s[j--] = c;
	}
}

int main(void)
{
	char str[MAXLEN];

	printf("Enter a string to reverse:\n");
	scanf("%s", str);
	reverse(str);
	printf("%s\n", str);	

	return 0;
}
