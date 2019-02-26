/*
 * Exercise 8-4. The standard library function
 *
 * 		int fseek(FILE *fp, long offset, int origin)
 *
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and the return value is an int status, not a position. Write
 * fseek. Make sure that your fseek coordinates properly with the buffering
 * done for the other functions of the library.
 *
 * By Faisal Saadatmand
 */

#define EOF        (-1)
#define BUFSIZ     1024
#define OPEN_MAX   20                  /* max #files open at once */

typedef struct _iobuf {
	int  cnt;                          /* characters left */
	char *ptr;                         /* next character position */
	char *base;                        /* location of buffer */
	int  flag;                         /* mode of file access */
	int  fd;                           /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
	_READ    = 01,                     /* file open for reading */
	_WRITE   = 02,                     /* file open for writing */
	_UNBUF   = 04,                     /* file is unbuffered */
	_EOF     = 010,                    /* EOF has occurred on this file */
	_ERR     = 020,                    /* error occurred on this file */
};

/* functions */
FILE *_fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose (FILE *);
int fseek(FILE *, long, int);

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

/* _fopen: open file, return ptr */
FILE *_fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)              /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;                /* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fileno(fp), fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
		return EOF;

	if (fp->flag & _UNBUF)
		bufsize = 1;
	else if (fp->flag & _EOF)          /* flush written data only (fflush) */
		bufsize = BUFSIZ - fp->cnt;
	else
		bufsize = BUFSIZ;

	if (fp->base == NULL) {            /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;                /* can't get buffer */
		*fp->base = '\0';              /* initialize string */
	}
	fp->ptr = fp->base;
	if (bufsize == 1)                  /* unbuffered output */
		*fp->ptr = x;
	if (*fp->ptr != '\0' || bufsize == 1) {
		fp->cnt = write(fileno(fp), fp->ptr, bufsize);
		if (fp->cnt != bufsize) {
			if (fp->cnt == -1)
				fp->flag |= _EOF;
			else
				fp->flag |= _ERR;
			fp->cnt = 0;
			return EOF;
		}
	}
	if (bufsize != 1) {                /* buffered output */
		*fp->ptr = x;
		fp->cnt = BUFSIZ - 1;          /* reset counter */
	}
	return (unsigned char) *fp->ptr++ ;
}

/* fflush: on output stream, write unwritten buffered data. On input stream,
 * the effect is undefined. NULL flushes all output streams. */
int fflush(FILE *fp)
{
	FILE *cond;                        /* loop condition */
	
	if (fp == NULL) {                  /* flush all output stream */
		fp = _iob;
		cond = _iob + OPEN_MAX;
	} else                             /* flush fp's buffer */
		cond = fp + 1;
	for ( ; fp < cond; fp++) {
		if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
			return EOF;
		fp->flag |= _EOF;              /* singal EOF to _flushbuf */
		if (_flushbuf(*fp->ptr, fp) < 0)
			return EOF;
		*fp->ptr = '\0';
		fp->cnt = 0;
	}
	return 0;
}

/* fclose: flushes unwritten date from stream, discard unread buffered input,
 * frees allocated memory, and closes stream. */
int fclose (FILE *fp)
{
	if ((fp->flag & (_WRITE | _EOF | _ERR)) == _WRITE)
		if (fflush(fp) < 0)
			return EOF;
	free(fp->base);
	if (close(fileno(fp)) < 0) {
		fp->flag |= _ERR;
		return EOF;
	}
	return 0;
}

/* fseek: sets the file position indicator for fp  */
int fseek(FILE *fp, long offset, int origin)
{
	if ((fp->flag & (_WRITE | _READ)) == 0)
		return -1;
	if (lseek(fileno(fp), offset, origin) < 0) {
		fp->flag |= _ERR;
		return -1;
	}
	fp->ptr = fp->base;                /* reset buffer */
	*fp->ptr = '\0';
	fp->cnt = 0;
	fp->flag &= ~(_EOF);
	return 0;
}

FILE _iob[OPEN_MAX] = {                /* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;

	if (argc == 1)
		while ((c = getchar()) != EOF)
			putchar(c);
	else
		while (--argc > 0)
			if ((fp = _fopen(*++argv, "r")) == NULL)
				exit(EXIT_FAILURE);
			else {
				while ((c = getc(fp)) != EOF)
					putchar(c);
	//			fseek(fp, -5L, 1);
	//			while ((c = getc(fp)) != EOF)
	//				putchar(c);
				fclose(fp);
			}
	if (ferror(stdout))
		exit(EXIT_FAILURE);
	fclose(stdout);
	exit(0);
}
