/* 
 * Exercise 5-12. Extend entab and detab to accpt the shorthand
 *
 * 		entab -m +n
 *
 * 	to mean tab stops every n columns, starting at column m. Choose convenient
 * 	(for the user) default behaviour.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000 /* max length of input/output line */
#define MAXTABS 100 /* max number of tab stop positions */

/* functions */
int getLine(char *, int);
void entab(char *, char *, int *, int *);
int expandArg(int, char **, int *, int *);

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

	if (count == 1) /* no options provided */
		return 0; /* signal to use default n and m */

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
			return -1;
		}
	}
	if (posError) {
		printf("%s: invalid position: %s\n", prog, *list);
		return -1;
	}
	return 1;
}

/* entab function: replaces blanks with the minimum number of tabs and blanks */
void entab(char *in, char *out, int *n, int *m)
{
	int i; /* index for read line */
	int j; /* index for modified (written) line */
	int nblanks; /* number of required blanks */
	int ntabs; /* number of required tabs */
	
	for (i = j = 0; in[i] != '\0'; ++i) {
		if (in[i] == ' ') {
			for (nblanks = ntabs = 0; in[i] == ' '; ++i) { /* count blanks */
				if (i + 1 >= *m && (i + 1) % *n == 0) { /* replace every N blanks with a tab */
					++ntabs;
					nblanks = 0; /* reset */
				} else
					++nblanks;
			}
			--i; /* adjust position after the loop */
			while (ntabs-- > 0) /* insert tabs */
				out[j++] = '\t';
			while (nblanks-- > 0) /* insert remaining blanks */
				out[j++] = ' ';
		} else 
			out[j++] = in[i]; /* copy all other characters */
	}
	out[j] = '\0';
}

int main(int argc, char *argv[])
{
	char in[MAXLEN]; /* currently read line */
	char out[MAXLEN]; /* modified line */
	int n = 4; /* default tabstops (every n columns) */
	int m = 1; /* default starting position for tabstops */

	if (expandArg(argc, argv, &n, &m) < 0)
		return 1;
	while (getLine(in, MAXLEN) > 0) {
		entab(in, out, &n, &m);
		printf("%s", out);
	}
	return 0;
}
