/* 
 * Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
float toCelsius(float);

float toCelsius(float f)
{
	return (5.0 / 9.0) * (f - 32.0);
}

int main(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;        /* lower limit of temperature scale */
	upper = 300;      /* upper limit */
	step  = 20;       /* step size */

	fahr = lower;
	printf("Fahrenheit\tCelsius\n");
	while (fahr <= upper) {
		celsius = toCelsius(fahr);
		printf("%10.0f\t%7.1f\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}
