/*
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two version.
 *
 * By Faisal Saadatmand
 */

 /* Note: this version of cat is faster */

#include <unistd.h>                    /* for read and write */
#include <fcntl.h>                     /* for open and close */
#include <stdio.h>                     /* also needed for BUFSIZ */
#include <stdlib.h>
#include <stdarg.h>

#define IN    0                        /* standard input file */
#define OUT   1                        /* standard output file */
#define ERROR 2                        /* standard error file */

/* functions */
void filecopy(int, int);
void error(char *, ...);

void filecopy(int in, int out)
{
	char buf[BUFSIZ];
	int n;

	while ((n = read(in, buf, BUFSIZ)) > 0)
		write(out, buf, n);
}

/* error: print an error message and die */
void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd;                            /* file descriptor */
	char *prog = argv[0];              /* program name */

	if (argc == 1)
		filecopy(IN, OUT);
	else
		while (--argc > 0)
			if ((fd = open(argv[1], O_RDONLY, 0)) == -1)
				error("%s: can't open %s", prog, argv[1]);
			else {
				filecopy(fd, OUT);
				close(fd);
			}
	exit(EXIT_SUCCESS);
}
