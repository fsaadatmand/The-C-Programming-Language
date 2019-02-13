/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with
 * only one test inside the loop and measure the difference in run-time.
 *
 * Answer: binSearch_alt algorithm is faster because it has one less
 * comparison in the loop; However it doesn't stop when the number is found in
 * the loop.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define SIZE 12

/* functions */
int binSearch(int, int [], int);
int binSearch_alt(int, int [], int);

/* binSearch: find x in value[0] <= value[1] <= ... <= value[n - 1] */
int binSearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;    /* match found */
	}
	return -1;             /* no match */
}

int binSearch_alt(int x, int v[], int n)
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
		return low;
	return -1;
}

int main(void)
{
	int array[SIZE] = { 2, 4, 5, 6, 8, 9, 12, 16, 20, 32, 40, 78 };
	int number = 0;

	printf("Enter number to search in the array: ");
	while (scanf("%i", &number) != EOF) {
		printf("%i\n", binSearch_alt(number, array, SIZE));
		printf("Enter number to search in the array: ");
	}
	return 0;
}
