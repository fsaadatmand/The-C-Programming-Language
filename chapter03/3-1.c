/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with
 * only one test inside the loop and measure the difference in run-time.
 *
 * By Faisal Saadatmand
 */

/*
 * Answer: this version  is faster because it has one less comparison in the
 * loop; However, it doesn't stop the loop as soon as the match is found.
 * the loop.
 */

#include <stdio.h>

#define SIZE 12

/* functions */
int binSearch(int, int [], int);

/* binSearch: find x in value[0] <= value[1] <= ... <= value[n - 1] */
int binSearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (v[mid] < x)
			low = mid + 1;
		else
			high = mid;
	}
	if (v[low] == x)
		return low; /* found match */
	return -1; /* no match */
}

int main(void)
{
	int array[SIZE] = { 2, 4, 5, 6, 8, 9, 12, 16, 20, 32, 40, 78 };
	int input, number;

	while (1) {
		printf("Enter number to search in the array: ");
		input = scanf("%i", &number);
		if (!input || input == EOF)
			return -1;
		printf("%i\n", binSearch(number, array, SIZE));
	}
	return 0;
}
