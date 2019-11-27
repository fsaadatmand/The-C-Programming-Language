/* 
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 *
 * 		entab -m +n
 *
 * to mean tab stops every n columns, starting at column m. Choose convenient
 * (for the user) default behaviour.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000 /* max length of input/output line */

/* functions */
int getLine(char *, int);
int expandArg(int, char **, int *, int *);
void detab(char *, char *, int *, int *);

/* getLine function: read a line into s, return length */
int getLine(char *s, int lim)
{
	int c;
	char *len;

	len = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return strlen(len);
}

int expandArg(int count, char **list, int *n, int *m)
{
	int posError;
	char *prog = *list;

	posError = 0;
	while (--count > 0) {
		if (strcmp(*++list, "-m") == 0) {
			if ((*m = atoi(*++list)) < 1) {
				posError = 1;
				break;
			}
			--count;
		} else if (strcmp(*list, "+n") == 0) {
			if ((*n = atoi(*++list)) < 1) {
				posError = 1;
				break;
			}
			--count;
		} else {
			printf("Usage: %s [-m pos] [+n pos]\n", prog);
			return 0;
		}
	}
	if (posError) {
		printf("%s: invalid position: %s\n", prog, *list);
		return 0;
	}
	return 1;
}

/* detab function: replaces tabs with the proper number of blanks */
void detab(char *in, char *out, int *n, int *m)
{
	int i; /* index for read line */
	int j; /* index for modified (written) line */
	int nblanks; /* number of required blanks */

	for (i = j = 0; in[i] != '\0'; ++i)
		if ((j + 1) >= *m && in[i] == '\t') {
			nblanks =  *n - (j % *n);
			while (nblanks-- > 0)
				out[j++] = ' ';
		} else 
			out[j++] = in[i];
	out[j] = '\0';
}

int main(int argc, char *argv[])
{
	char in[MAXLEN]; /* currently read line */
	char out[MAXLEN]; /* modified line */
	int n = 4; /* default tabstops (every n columns) */
	int m = 1; /* default starting position for tabstops */

	if (expandArg(argc, argv, &n, &m))
		while (getLine(in, MAXLEN) > 0) {
			detab(in, out, &n, &m);
			printf("%s", out);
		}
	return 0;
}
