/* 
 * program that prints Fahrenheit-Celsius convertion table
 * for fahr = 0, 20, ..., 300; floating-point version
 * Modification: print table header.
 */

#include <stdio.h>

int main(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;        /* lower limit of temperatuire scale */
	upper = 300;      /* upper limit */
	step  = 20;       /* step size */

	fahr = lower;

	printf("Fahrenheit\tCelsius\n");

	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.0f\t%7.1f\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}
