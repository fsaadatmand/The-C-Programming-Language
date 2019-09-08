/*
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
 * input from a set named files or, if no files are named as arguments, from
 * the standard input. Should the file name be printed when a matching line is
 * found?
 *
 * Answer: of course!
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

/* globals */
char *progName;

/* functions */
int getLine(char *, size_t, FILE *);
FILE* loadFile(char *);
int findPattern(FILE *, char *, char *, int, int);

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
		fprintf(stderr, "%s: can't open %s\n", progName, fileName);
		exit(EXIT_FAILURE);
	}
	return fp;
}

int findPattern(FILE *fp, char *fileName, char *pattern, int except, int number)
{
	char line[MAXLINE];
	long int lineno, found = 0;

	for (lineno = 1; getLine(line, MAXLINE, fp) > 0; lineno++)
		if ((strstr(line, pattern) != NULL) != except) {
			if (fileName)
				printf("%s:", fileName);
			if (number)
				printf ("%ld:", lineno);
			printf("%s", line);
			found++;
		}
	return found;
}

/* find: print lines that match pattern from 1s arg */
int main(int argc, char *argv[])
{
	int c, except = 0, number = 0, found = 0;
	char *pattern = NULL;
	FILE *file = NULL;

	progName = argv[0];
	while (--argc > 0 && (*++argv)[0] == '-')    /* check for flags */
		while ((c = *++argv[0]))
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("%s: illegal option %c\n", progName, c);
				argc = 0;
				found = -1;
				break;
			}

	pattern = *argv;                   /* save a pointer to the pattern */
	if (argc < 1)
		printf("Usage: %s -x -n pattern\n", progName);
	else if (argc == 1)                /* input from stdin */
		found += findPattern(stdin, NULL, pattern, except, number);
	else                               /* input from file or set of files */
		while (argc-- > 1) {
			file = loadFile(*++argv);
			found += findPattern(file, *argv, pattern, except, number);
			fclose(file);
		}
	return found;
}
