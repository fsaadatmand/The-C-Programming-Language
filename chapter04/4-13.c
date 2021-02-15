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
void reverse(char s[]);
void reverse_inplace(char str[], int begin, int end);
void swap(char arr[], size_t i, size_t j);

/* reverse: interface function to reverse_inplace */
void reverse(char s[])
{
	reverse_inplace(s, 0, strlen(s) - 1);
}

/* reverse_inplace: reverse string s in place, recursive version */
void reverse_inplace(char str[], int begin, int end)
{
	if (begin > end) /* exit condition */
		return;
	swap(str, begin, end);
	reverse_inplace(str, ++begin, --end);
}

/* swap: interchange v[i] and v[j] */
void swap(char v[], size_t i, size_t j)
{
	char tmp;
	
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int main(void)
{
	char str[MAXLEN];

	printf("Enter a string to reverse: ");
	scanf("%s", str);
	reverse(str);
	printf("%s\n", str);	

	return 0;
}
