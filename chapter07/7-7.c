/*
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
 * input from a set named files or, if no files are named as arguments, from
 * the standard input. Should the file name be printed when a matching line is
 * found?
 * Answer: of course!
 *
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

/* fucntions */
int getLine(char *, int);

/* getLine: get line into s, return length */
int getLine(char *line, int max)
{
	int c, i;

	i = 0;
	while (--max > 0 && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}

/* fgetLine: read line, return length - fgets version */
int fgetLine(FILE *fp, char *line, int max)
{
	if (fgets(line, max, fp) == NULL)
		return 0;
	else
		return strlen(line);
}

/* find: print lines that match pattern from 1s arg */
int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno;
	int c, except = 0, number = 0, found = 0;
	char *prog = argv[0];
	char *pattern;
	FILE *fp;

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
				printf("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}

	if (argc < 1)
		printf("Usage: find -x -n pattern\n");
	else if (argc == 1) {              /* input from stdin */
		for (lineno = 1; getLine(line, MAXLINE) > 0; lineno++)
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf ("%ld:", lineno);
				printf("%s", line);
				found++;
			}
	} else {                           /* input from file or set of files */
		pattern = *argv;               /* save a pointer to the pattern */
		while (argc-- > 1) {
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(EXIT_FAILURE);
			}
			while (!feof(fp))
				for (lineno = 1; fgetLine(fp, line, MAXLINE) > 0; lineno++)
					if ((strstr(line, pattern) != NULL) != except) {
						printf("%s:", *argv);    /* print file name */
						if (number)
							printf ("%ld:", lineno);
						printf("%s", line);
						found++;
					}
			fclose(fp);
		}
	}
	return found;
}
