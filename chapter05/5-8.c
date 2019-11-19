/*
 * Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy
 * this defect.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day; return -1 on invalid input */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (year < 0 || month < 1 ||  month > 12 || day < 1 || day > 31)
		return -1;
	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year; zero value is an invalid input */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	if (year < 0 || yearday < 1 || yearday > 366) {
		*pmonth = *pday =  0;
		return;
	}
	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main(void)
{
	int yearday, month, day;

	if ((yearday = day_of_year(1986, 3, 35)) < 0)
		printf("Invalid input\n");
	else
		printf("day of the year: %i\n", yearday);
	month_day(2020, 367, &month, &day);
	if (!month || !day)
		printf("Invalid input\n");
	else
		printf("month %i, day %i\n", month, day);
	return 0;
}
