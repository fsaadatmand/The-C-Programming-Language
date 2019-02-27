/*
 * Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry.
 * By Faisal Saadatmand
 */

#define _XOPEN_SOURCE                /* for modern Unix sys/stat.h */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>                     /* flags for read and write */
#include <sys/types.h>                 /* typedefs */
#include <sys/stat.h>                  /* structure returned by stat */
#include "dirent.h"
#include <stdlib.h>                    /* for malloc */
#include <time.h>

#include <sys/stat.h>                  /* structure returned by stat */

#define MAX_PATH     1024
#define MAX_TIME     60
#ifndef DIRSIZE
#define DIRSIZE      14
#endif

struct direct                          /* directory */
{
	ino_t d_ino;                       /* inode number */
	char d_name[DIRSIZE];              /* long name does not have '\0' */
};

/* functions */
void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));
int fstat(int fd, struct stat *);
void timefmt(char *, int,  time_t *);

/* timefmt: format unix time into local time */
void timefmt(char *buffer, int bufsize,  time_t *utime)
{
	struct tm brokentime;
	struct tm *tp = &brokentime;

	tp = localtime(utime);             /* Unix time to broken local time time */
	strftime(buffer, bufsize, "%b %d %H:%M ", tp);
}

/* fsize: print size of file name */
void fsize(char *name)
{
	struct stat stbuf;
	char *time;                        /* formated time */

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);

	if ((time = (char *) malloc(MAX_TIME)) == NULL) {
		fprintf(stderr, "fsize: can't allocate memory to buffer  %s\n", name);
		exit(EXIT_FAILURE);
	}

	timefmt(time, MAX_TIME, &stbuf.st_mtime);
	printf("%o %lu %u %u %8ld %s %s\n", stbuf.st_mode, stbuf.st_nlink,
			stbuf.st_uid, stbuf.st_gid, stbuf.st_size, time, name);
	free(time);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *name))
{
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0
				|| strcmp(dp->name, "..") == 0)
			continue;                  /* skip self and parent */
		if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}

/* opendir: open a directory for readdir calls */
DIR *opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
			|| fstat(fd, &stbuf) == -1
			|| (stbuf.st_mode & S_IFMT) != S_IFDIR
			|| (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/* closedir: close directory opened by opendir */
void closedir(DIR *dp)
{
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

/* readdir: read directory entries in sequence */
Dirent *readdir(DIR *dp)
{
	struct direct dirbuf;              /* local directory structure */
	static Dirent d;                   /* return: portable structure */

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0)         /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZE);
		d.name[DIRSIZE - 1] = '\0';        /* ensure termination */
		return &d;
	}
	return NULL;
}

/* print file size */
int main(int argc, char **argv)        /* **argv == *argv[] */
{
	if (argc == 1)                     /* default: current directory */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}
