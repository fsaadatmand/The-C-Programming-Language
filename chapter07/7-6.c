/*
 * Exercise 7-6. Write a program to compare two file, printing the first line
 * where they differ.
 * By Faisal Saadatmand
 */

#define MAXFILES  3
#define MAXLEN    1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* functions */
int  getLine(FILE *, char *, int);

/* getLine: read line, return length - fgets version */
int getLine(FILE *fp, char *line, int max)
{
	if (fgets(line, max, fp) == NULL)
		return 0;
	else
		return strlen(line);
}

int main(int argc, char *argv[])
{
	FILE *file[MAXFILES];                  /* array to store files */
	char *prog = argv[0];                  /* program name for errors */
	char *f1name = argv[1];                /* file 1 name for printing line */
	char *f2name = argv[2];                /* file 2 name for printing line */
	char f1line[MAXLEN], f2line[MAXLEN];   /* currently read line */
	int  f1ln, f2ln;                       /* currently read line number */
	int  result, i;
	
	if (argc != 3) {                       /* wrong format */
		fprintf(stderr, "Use: %s file1 file2\n", prog);
		exit(EXIT_FAILURE);
	}

	/* open files */
	for (i = 1; --argc > 0; ++i)           /* skip file[0] for readability */
		if ((file[i] = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(EXIT_FAILURE);
		}

	f1ln = f2ln = result = 0;
	while (!feof(file[1]) || !feof(file[2])) { 
		if (getLine(file[1], f1line, MAXLEN) > 0)
			f1ln++;                        /* count successfully read lines */
		if (getLine(file[2], f2line, MAXLEN) > 0)
			f2ln++;                        /* count successfully read lines */

		if ((result = strcmp(f1line, f2line)) != 0)
			break;                         /* found mismatching line */
	}

	if (result != 0) {
		fprintf(stdout, "%s: %i: %s", f1name, f1ln, f1line);
		fprintf(stdout, "%s: %i: %s", f2name, f2ln, f2line);
	} else
		printf("%s and %s are identical\n", f1name, f2name);

	fclose(file[1]);
	fclose(file[2]);

	exit(EXIT_SUCCESS);
}
