f/*
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch?  
 *
 * Answer: ungets should know about buf and bufp so as to be independent of
 * ungetc, in the case latter is not needed. Moreover, if the buffer overloaded
 * ungets would print the error rather than ungetch, which makes it easier to
 * debug errors.
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
void   ungets(char *);

/* globals */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */
char   s[MAXLEN];

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
void ungets(char *s)
{
	int len;

	for (len = strlen(s); len >= 0 ; --len)
		if (bufp >= BUFSIZE)
			printf("ungets: too many characters\n");
		else
			buf[bufp++] = s[len];
}

/* test ungets */
int main(void)
{
	int c, i;

	i = 0;
	while ((s[i++] = getch()) != '\n')
		;

	s[i] = '\0';
	ungets(s);

	while ((c = getch()) != EOF)
		putchar(c);
	return 0;
}
