/*
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch?  
 *
 * Answer: on one hand, the only clear advantage in ungets gaining direct
 * access to buf and bufp seems to be the ability to print the error message
 * directly rather than through ungetch. On the other, since ungetc is just
 * ungetch wrapped in a for loop, it makes sense to use ungetch and reduce code
 * duplication.
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>          /* for strlen() */

#define BUFSIZE     100
#define MAXLEN      10000

/* functions */
int    getch(void);
void   ungetch(int);
void   ungets(char []);

/* globals */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungerch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* ungets: push back s onto the input */
void ungets(char s[])
{
	int len;

	for (len = strlen(s) - 1; len >= 0 ; --len)
			ungetch(s[len]);
}

/* test ungets */
int main(void)
{
	int c, i;
	char   s[MAXLEN];

	printf("Enter string to test ungets function: ");
	for (i = 0; (s[i] = getch()) != '\n'; i++)
		;
	s[i++] ='\n';
	ungets(s);

	while ((c = getch()) != EOF)
		putchar(c);
	return 0;
}
