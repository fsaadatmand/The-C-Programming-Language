/*
 * Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file.
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXHEADER     6             /* maximum header size */
#define MAXFOOTER     3             /* maximum footer size */
#define MAXLINE      80             /* maximum characters per line */
#define MAXPAGE      60             /* maximum lines per page */

/* globals */
const char *progName;

/* functions */
FILE* loadFile(char *);
int printHeader(char *, int);
void printFile(FILE *, char *);

FILE* loadFile(char *fileName)
{
	FILE *fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "%s: can't open %s\n", progName, fileName);
		exit(EXIT_FAILURE);
	}
	return fp;
}

int printHeader(char *fileName, int pageNo)
{
	int ln = 5;     /* length of the lines bellow */

	printf("\n************************\n");
	printf("File name: %s\n", fileName);
	printf("Page: %i\n", pageNo);
	printf("************************\n");
	while (ln++ < MAXHEADER)
		fprintf(stdout, "\n");
	return ln;
}

void printFile(FILE *file, char *fileName)
{
	char line[MAXLINE];
	int lineNo,pageNo;

	lineNo = pageNo = 1;
	while (fgets(line, MAXLINE, file)) {
		if (lineNo == 1) {
			fprintf(stdout, "\f");
			lineNo = printHeader(fileName, pageNo++);
		}
		fputs(line, stdout);
		if (++lineNo > MAXPAGE - MAXFOOTER)
			lineNo = 1;
	}
	fprintf(stdout, "\f");
}

int main(int argc, char *argv[])
{
	FILE *fp;

	progName = *argv;
	if (argc == 1)               /* standard input */
		printFile(stdin, "standard input");
	else
		while (--argc > 0) {
			fp = loadFile(*++argv);
			printFile(fp, *argv);
			fclose(fp);
		}
	exit(EXIT_SUCCESS);
}
