#define NAME_MAX 14                    /* longest filename; system-dependent */

typedef struct {                       /* portable directory entry; */
	long ino;                          /* inode number */
	char name[NAME_MAX];               /* name + '\0' terminator */
} Dirent;

typedef struct {                       /* minimal DIR: no buffering, etc. */
	int fd;                            /* file descriptor for directory */
	Dirent d;                          /* the directory entry */
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);
