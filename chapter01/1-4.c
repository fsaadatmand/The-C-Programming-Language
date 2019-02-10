/* 
 * Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit table.
 * By Faisal Saadatmand
 */

#include <stdio.h>

int main(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;        /* lower limit of temperature scale */
	upper = 300;      /* upper limit */
	step  = 20;       /* step size */

	fahr = celsius = lower;

	printf("Celsius\t\tFahrenheit\n");

	while (celsius <= upper) {
		fahr = celsius * 9 / 5 + 32;
		printf("%7.0f\t%18.0f\n", celsius, fahr);
		fahr = fahr + step;
		celsius = celsius + step;
	}
	return 0;
}
