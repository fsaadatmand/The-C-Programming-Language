/* 
 * Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion.
 * By Faisal Saadatmand
 */

#include <stdio.h>

float fahrToCelsius(float fahr)
{
	float celsius;

	celsius = (5.0 / 9.0) * (fahr-32.0);

	return celsius;
}

int main(void)
{
	float fahrToCelsius(float);

	float fahr, celsius;
	float lower, upper, step;

	lower = 0;        /* lower limit of temperature scale */
	upper = 300;      /* upper limit */
	step  = 20;       /* step size */

	fahr = lower;

	printf("Fahrenheit\tCelsius\n");

	while (fahr <= upper) {
		celsius = fahrToCelsius(fahr);
		printf("%10.0f\t%7.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return 0;
}
