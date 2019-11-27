#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

#define NUMBER   '0' /* signal that a number was found */
#define NAME     '1' /* signal that a string command was found */

int atoi(const char *);
double atof(const char *);
void itoa(int , char *);
int getLine(char *, int);
int getop(char *);
void reverse(char *);
int strindex(const char *, const char *);

#endif /* FUNCTIONS_H */
