/*
 * Exercise 7-4. Write a private version of scanf analogous to minprintf from
 * the previous section.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int minscanf(char *, ...);

int minscanf(char *format, ...)
{
	va_list ap;
	char *p, *sval, *cval;
	int *ival;
	float *fval;
	unsigned *uval;
	int nchar = 0;

	va_start(ap, format);              /* make ap point to 1st unnamed arg */
	for (p = format; *p; p++) {
		if (*p != '%')
			continue;

		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int *);
			nchar += scanf("%d", ival);
			break;
		case 'i':
			ival = va_arg(ap, int *);
			nchar += scanf("%i", ival);
			break;
		case 'o':
			uval = va_arg(ap, unsigned *);
			nchar += scanf("%u", uval);
			break;
		case 'c':
			cval = va_arg(ap, char *);
			nchar += scanf("%c", cval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			nchar += scanf("%s", sval);
			break;
		case 'e':
			fval = va_arg(ap, float *);
			nchar += scanf("%e", fval);
			break;
		case 'f':
			fval = va_arg(ap, float *);
			nchar += scanf("%f", fval);
			break;
		case 'g':
			fval = va_arg(ap, float *);
			nchar += scanf("%g", fval);
			break;
		default:
			break;
		}
		va_end(ap);
	}
	return nchar;
}

int main(void) {
	int x, y, z;
	int nchar;

	printf("Enter 3 integers: ");
	nchar = minscanf("%i %i %i", &x, &y, &z);
	printf("%i %i %i\n", x, y, z);
	printf("Number of elements: %i\n", nchar);

	return 0;
}
