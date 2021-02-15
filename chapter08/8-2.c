/*
 * Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. Compare code size and execution speed.
 *
 * By Faisal Saadatmand
 */

#define EOF        (-1)
#define BUFSIZ     1024
#define OPEN_MAX   20                  /* max #files open at once */

typedef struct {
	unsigned int _READ : 1;            /* file open for reading */
	unsigned int _WRITE : 1;           /* file open for writing */
	unsigned int _UNBUF : 1;           /* file is unbuffered */
	unsigned int _EOF : 1;             /* EOF has occurred on this file */
	unsigned int _ERR : 1;             /* error occurred on this file */
} field;

typedef struct _iobuf {
	int  cnt;                          /* characters left */
	char *ptr;                         /* next character position */
	char *base;                        /* location of buffer */
	field flag;                        /* mode of file access */
	int  fd;                           /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

/* functions */
FILE *_fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)    (((p)->flag & _EOF) != 0)
#define ferror(p)  (((p)->flag & _ERR) != 0)
#define fileno(p)  ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>                    /* for malloc */

#define PERMS 0666                     /* RW for owner, group, others */

/* fopen: open file, return ptr */
FILE *_fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag._READ == 0 && fp->flag._WRITE == 0))
			break;                     /* found free slot */
	if ( fp >= _iob + OPEN_MAX)        /* no free slots */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;                   /* couldn't access name */
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	(*mode == 'r') ? (fp->flag._READ = 1) : (fp->flag._WRITE = 1);
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->flag._READ == 0)
		return EOF;
	bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL)              /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;                /* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag._EOF = 1;
		else
			fp->flag._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp)
{
	int bufsize;

	if (fp->flag._WRITE == 0) 
		return EOF;
	bufsize = (fp->flag._UNBUF == 1) ? BUFSIZ : 1;
	if (fp->base == NULL) {            /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;                /* can't get buffer */
		*fp->base = '\0';              /* initialize string */
	}
	fp->ptr = fp->base;
	if (bufsize == 1)                  /* unbuffered output */
		*fp->ptr = x;
	if (*fp->ptr != '\0' || bufsize == 1) {
		fp->cnt = write(fp->fd, fp->ptr, bufsize);
		if (--fp->cnt != bufsize) {
			fp->flag._ERR = 1;
			fp->cnt = 0;
			return EOF;
		}
	}
	if (bufsize > 1) {                  /* buffered output */
		*fp->ptr = x;
		fp->cnt = BUFSIZ - 1;           /* set character left counter */
	}
	return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {                 /* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, {1, 0, 0 , 0, 0}, 0 },
	{ 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0} , 2 }
};

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;

	if (argc == 1) {
		while ((c = getchar()) != EOF)
			putchar(c);
	} else 
		while (--argc > 0) 
			if ((fp = _fopen(*++argv, "r")) == NULL)
				exit(EXIT_FAILURE);
			else
				while ((c = getc(fp)) != EOF)
					putchar(c);
	exit(0);
}
