#include <stdio.h>

int binSearchOld(int x, int v[], int n);
int binSearch(int x, int value[], int n);

/* binSearch: find x in value[0] <= value[1] <= ... <= value[n - 1] */
int binSearchOld(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;    /* match found */
	}
	return -1;             /* no match */
}

int binSearch(int x, int value[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (mid != low && low < high) {
		mid = (low + high) / 2;
		if (x <= value[mid])
			high = mid;
		else
			low = mid + 1;
	}

	if (x == value[mid])
		return mid;        /* match found */
	else
		return -1;         /* no match */
}
int main(void)
{
	int i;
	int array[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	
//	for (i = 0; i <= 1000000000; ++i)
//		binSearchOld(6, array, 12);
//		printf("%i\n", binSearchOld(6, array, 12));
	for (i = 0; i <= 1000000000; ++i)
		binSearch(6, array, 12);           /* faster! */
		printf("%i\n", binSearch(6, array, 12));

	return 0;
}
