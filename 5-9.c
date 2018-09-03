/*
 * Exercise 5-9. Rewrite the routine day_of_year and month_day with pointers
 * instead of indexing.
 * By Faisal Saadatmand
 */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
char *month_name(int n); 

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

	char (*pdaytab)[13] = daytab;     /* pointer to daytab[0][0] */

/* day_of_year: set day of year from month & day; return -1 on invalid input */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if ((year < 1) || (month < 1 && month > 12) || (day < 1 && day > 31))
		return -1;

	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;
	
	for (i = 1; i < month; i++)
		day += *((*(pdaytab + leap)) + i); 
		//day += *(daytab[leap] + i);
		//day += (*(daytab + leap)) [i];
		//day += *((*(daytab + leap)) + i);
		//day += *(&daytab[0][0] + 4 * leap + i);

	return day;
}

/* month_day: set month, day from day of year; zero value is an invalid input */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = (year % 4 == 0 && year % 100) || year % 400 == 0;

	for (i = 1; yearday > daytab[leap][i]; i++)
		//yearday -= daytab[leap][i];
		yearday -= *(*(pdaytab + leap) + i); 

	(i < 1 || i > 12 || year < 1) ? (*pmonth = **pdaytab) : (*pmonth = i);
	(yearday < 1 || yearday > 366 || year < 1) ? (*pday = **pdaytab) : 
		(*pday = yearday);
}

/* month_name: return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"illegal month",
		"january", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(void)
{
	int yearday, month, day;

	if ((yearday = day_of_year(2018, 9, 3)) >= 0)
		printf("%i day of the year\n", yearday);
	else
		printf("invalid input\n");

	month_day(2018, 246, &month, &day);

	if (month != 0 && day != 0)
		printf("%s %i\n", month_name(month), day);
	else
		printf("invalid input\n");

	return 0;
}
