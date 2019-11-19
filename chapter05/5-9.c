/*
 * Exercise 5-9. Rewrite the routine day_of_year and month_day with pointers
 * instead of indexing.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* functions */
int day_of_year(int, int, int);
void month_day(int, int, int *, int *);
char *month_name(int); 

static char daytab[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

char (*pdaytab)[13] = daytab;     /* pointer to first element (1st array) */
                                  /* we could also use datab name directly */

/* day_of_year: set day of year from month & day; return -1 on invalid input */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if ((year < 1) || month < 1 || month > 12 || day < 1 || day > 31)
		return -1;
	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
	for (i = 1; i < month; i++)
		day += *(*(pdaytab + leap) + i); 
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
		yearday -= *(*(pdaytab + leap) + i); 
	*pmonth = i;
	*pday = yearday;
}

/* month_name: return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"illegal month",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(void)
{
	int yearday, month, day;

	if ((yearday = day_of_year(2018, 9, 3)) < 0)
		printf("Invalid input\n");
	else
		printf("day of the year: %i\n", yearday);
	month_day(2018, 246, &month, &day);
	if (!month || !day)
		printf("Invalid input\n");
	else
		printf("%s %i\n", month_name(month), day);
	return 0;
}
