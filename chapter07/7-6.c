/*
 * Exercise 7-6. Write a program to compare two file, printing the first line
 * where they differ.
 *
 * By Faisal Saadatmand
 */

#define MAXLEN   1000    /* maximum line length */
#define MAXNAME  100     /* maximum length of file name */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* types */
typedef struct {
	char name[MAXNAME];  /* file name */
	FILE *fptr;          /* file pointer */
	char line[MAXLEN];   /* currently read line */
	int lineno;          /* number of read lines */
} File;

/* globals */
char *prog;              /* program name */

/* functions */
void openfile(const char *, File *);
void comparefiles(File *, File *);

void openfile(const char *filename, File *file)
{
	if (!(file->fptr = fopen(filename, "r"))) {
		fprintf(stderr, "%s: ca't open %s\n", prog, filename);
		exit(EXIT_FAILURE);
	}
	strcpy(file->name, filename);
	file->lineno = 0;
}

void comparefiles(File *f1, File *f2)
{
	do {
		if (fgets(f1->line, MAXLEN, f1->fptr))
			++f1->lineno;
		if (fgets(f2->line, MAXLEN, f2->fptr))
			++f2->lineno;
		if (!feof(f1->fptr) && !feof(f2->fptr)) /* are there lines? */
			if (strcmp(f1->line, f2->line)) /* compare lines */
				break; /* lines differ */
	} while (!feof(f1->fptr) && !feof(f2->fptr)); /* until either return EOF */
	if (!feof(f1->fptr))
		fprintf(stdout, "\n%s:%i: %s", f1->name, f1->lineno, f1->line);
	if (!feof(f2->fptr))
		fprintf(stdout, "\n%s:%i: %s", f2->name, f2->lineno, f2->line);
}

int main(int argc, char *argv[])
{
	File file_1, file_2;

	prog = *argv++;         /* program name for errors */
	if (--argc != 2) {      /* check cli argument */
		fprintf(stderr, "Usage: %s <file1> <file2>\n", prog);
		exit(EXIT_FAILURE);
	}
	openfile(*argv++, &file_1);
	openfile(*argv, &file_2);
	comparefiles(&file_1, &file_2);
	fclose(file_1.fptr);
	fclose(file_2.fptr);
	exit(EXIT_SUCCESS);
}
