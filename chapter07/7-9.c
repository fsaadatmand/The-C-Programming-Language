/*
 * Exercise 7-9. Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilities.
 *
 * Answer: I take it that by saving space the authors mean increasing code
 * compactness and by saving time reducing run time.  Implementing isupper() as
 * a macro avoids the overhead associated with calling a function on to the
 * stack memory; thus, we save time. I suppose it could be argued that this
 * saves stack memory as well, but I do not think that is what the authors
 * meant.  To save space, we could implement a macro such as IFUPPER that wraps
 * an "if ..."  statement around the isupper() function. The result is a
 * one-line code that performs multiple instructions. Moreover, if we avoid
 * using other functions in the wrapping and use nested macros instead, we
 * could save both time and space. The draw back, of course, is that the code,
 * though more readable, it will be full of unconventional idioms.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <ctype.h>

#define ISUPPER(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0            /* saves time */
#define TOLOWER(c) ((c)) + 'a' - 'A'                             /* saves time */
#define IFUPPER_TOLOWER(c) if (isupper((c))) (c) = tolower((c))  /* saves space */
#define IF_UPPER_TOLOWER(c) if (ISUPPER((c))) (c) = TOLOWER((c)) /* saves time and space */
#define IF_UPPER(c,a) (ISUPPER((c))) ? ((a)) : ((c))             /* saves time and space */

int main(void)
{
	int c;

	printf("Enter an upper case character: " );
	c = getchar();

	if (ISUPPER(c))
		c = tolower(c);
	printf("%c\n", c);

	IFUPPER_TOLOWER(c);
	printf("%c\n", c);

	IF_UPPER_TOLOWER(c);
	printf("%c\n", c);

	printf("%c", IF_UPPER(c, TOLOWER(c)));
	printf("\n");

	return 0;
}
