/*
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
 * input from a set named files or, if no files are named as arguments, from
 * the standard input. Should the file name be printed when a matching line is
 * found?
 *
 * By Faisal Saadatmand
 */

 /* Answer: only when files are named as arguments */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

/* globals */
char *prog;  /* program name */

/* functions */
int getLine(char *, size_t, FILE *);
FILE* loadFile(char *);
int findPattern(FILE *, const char *, const char *, const int, const int);

/* getLine: read line, return length - file pointer version */
int getLine(char *line, size_t max, FILE *fp)
{
	if (fgets(line, max, fp) == NULL)
		return 0;
	return strlen(line);
}

FILE* loadFile(char *fileName)
{
	FILE* fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "%s: can't open %s\n", prog, fileName);
		exit(EXIT_FAILURE);
	}
	return fp;
}

int findPattern(FILE *fp, const char *fileName, const char *pattern,
		const int except, const int number)
{
	char line[MAXLEN];
	long lineno;
	int found;

	lineno = found = 0;
	while (getLine(line, MAXLEN, fp) > 0) {
		++lineno;
		if ((strstr(line, pattern) != NULL) != except) {
			if (fileName)
				fprintf(stdout, "%s:", fileName);
			if (number)
				fprintf (stdout, "%ld:", lineno);
			fprintf(stdout, "%s", line);
			++found;
		}
	}
	return found;
}

/* find: print lines that match pattern from 1s arg */
int main(int argc, char *argv[])
{
	int c, except, number, found;
	char *pattern;
	FILE *file;

	prog = argv[0];
	except = number = found = 0;
	while (--argc > 0 && (*++argv)[0] == '-')  /* check for flags */
		while ((c = *++argv[0]))
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				fprintf(stderr, "%s: illegal option %c\n", prog, c);
				argc = 0;
				found = -1;
				break;
			}
	pattern = *argv++;          /* save a pointer to the pattern */
	if (argc < 1)
		fprintf(stderr, "Usage: %s [-xn] PATTERN [FILE...]\n", prog);
	else if (argc == 1)         /* input from stdin */
		found += findPattern(stdin, NULL, pattern, except, number);
	else                        /* input from file or set of files */
		while (argc-- > 1) {
			file = loadFile(*argv++);
			found += findPattern(file, *argv, pattern, except, number);
			fclose(file);
		}
	return found;
}
