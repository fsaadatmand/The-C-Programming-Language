/*
 * Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy
 * this defect.
 * By Faisal Saadatmand
 */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day; return -1 on invalid input */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if ((month < 1 && month > 12) || (day < 1 && day > 31))
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

	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	(i < 1 || i > 12) ? (*pmonth = daytab[0][0]) : (*pmonth = i);
	(yearday < 1 || yearday > 366) ? (*pday = daytab[0][0]) : (*pday = yearday);
}

int main(void)
{
	int yearday, month, day;

	if ((yearday = day_of_year(1977, 07, 22)) >= 0)
		printf("%i day of the year\n", yearday);
	else
		printf("invalid input\n");

	month_day(2020, 366, &month, &day);

	if (month != 0 && day != 0)
		printf("month %i, day %i\n", month, day);
	else
		printf("invalid input\n");

	return 0;
}
