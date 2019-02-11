/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside.) Write a version with
 * only one test inside the loop and measure the difference in run-time.
 * By Faisal Saadatmand
 */

#include <stdio.h>

int binSearchOld(int x, int v[], int n);
int binSearch(int x, int value[], int n);

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

int binSearch_new(int x, int value[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	mid = (low + high) / 2;
	while (low <= high | x != value[mid]) {
		mid = (low + high) / 2;
		if (x < value[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (x == value[mid])
		return mid;
	return -1;
}

int main(void)
{
	int array[12] = { 2, 4, 5, 6, 8, 9, 12, 16, 20, 32, 40, 78 };
	
		printf("%i\n", binSearch_new(2, array, 12));

	return 0;
}
