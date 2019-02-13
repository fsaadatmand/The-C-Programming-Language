/*
 * Exercise 7-3. Revise minprintf to handle more of the other facilities of
 * printf.
 * Note: flags (excepts for left adjust) and variable width and length are not implemented.
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUMB 20
#define FLT_PRCISION 6
#define FIELD_WIDTH 1

/* macros */
#define PRINT_N(la,x,w,v, nc) (la) ? (nc += printf("%-*" # x, w, v)) : \
	(nc += printf("%*" #x, w, v))
#define PRINT_D(la,x,w,p,v,nc) (la) ? (nc += printf("%-*.*" # x, w, p, v)) : \
	(nc += printf("%*.*" # x, w, p, v))

int minprintf(char *, ...);

/* minprintf: minimal printf with variable argument list */
int minprintf(char *fmt, ...)
{
	va_list ap;                        /* points to each unnamed arg in turn */
	char *p, *sval, number[MAXNUMB];
	int ival, i, width, precision, nchar = 0;
	double dval;
	unsigned uval;
	void *pval;
	int leftAdjust, *pival;


	va_start(ap, fmt);                 /* make ap point to 1st unnamed arg */

	for (p = fmt; *p; p++) {

		if (*p != '%') {
			putchar(*p);
			++nchar;
			continue;
		}

		leftAdjust = 0;
		width = 1;
		precision = -1;

		if (*++p == '-') {
			leftAdjust = 1;            /* left adjust */
			++p;
		}

		if (isdigit(*p)) {             /* get width */
			for (i = 0; isdigit(*p) && i < MAXNUMB; i++)
				number[i] = *p++; 
			number[i] = '\0';
			width = atoi(number);
		}
		if (*p == '.') {               
			++p;
			for (i = 0; isdigit(*p) && i < MAXNUMB; i++) /* get precision pts */
				number[i] = *p++; 
			number[i] = '\0';
			precision = atoi(number);
		}

		switch (*p) {
		case 'd':
			ival = va_arg(ap, int);
			PRINT_N(leftAdjust, d, width, ival, nchar);
			break;
		case 'i':
			ival = va_arg(ap, int);
			PRINT_N(leftAdjust, i, width, ival, nchar);
			break;
		case 'o':
			uval = va_arg(ap, int);
			PRINT_N(leftAdjust, o, width, uval, nchar);
			break;
		case 'x':
			uval = va_arg(ap, int);
			PRINT_N(leftAdjust, x, width, uval, nchar);
			break;
		case 'X':
			uval = va_arg(ap, int);
			PRINT_N(leftAdjust, X, width, uval, nchar);
			break;
		case 'u':
			uval = va_arg(ap, int);
			PRINT_N(leftAdjust, u, width, uval, nchar);
			break;
		case 'c':
			ival = va_arg(ap, int);
			PRINT_N(leftAdjust, c, width, ival, nchar);
			break;
		case 's':
			sval = va_arg(ap, char *);
			if (precision < 0)
				precision = strlen(sval);
			PRINT_D(leftAdjust, s, width, precision, sval, nchar);
			break;
		case 'f':
			dval = va_arg(ap, double);
			if (precision < 0)
				precision = FLT_PRCISION;
			PRINT_D(leftAdjust, f, width, precision, dval, nchar);
			break;
		case 'e':
			dval = va_arg(ap, double);
			if (precision < 0)
				precision = FLT_PRCISION;
			PRINT_D(leftAdjust, e, width, precision, dval, nchar);
			break;
		case 'E':
			dval = va_arg(ap, double);
			if (precision < 0)
				precision = FLT_PRCISION;
			PRINT_D(leftAdjust, E, width, precision, dval, nchar);
			break;
		case 'g':
			dval = va_arg(ap, double);
			PRINT_N(leftAdjust, g, width, dval, nchar);
			break;
		case 'G':
			dval = va_arg(ap, double);
			PRINT_N(leftAdjust, G, width, dval, nchar);
			break;
		case 'p':
			pval = va_arg(ap, void *); 
			PRINT_N(leftAdjust, p, width, pval, nchar);
			break;
		case 'n':
			pival = va_arg(ap, int *);
			*pival = nchar;
			break;
		default:
			putchar(*p);
			++nchar;
			break;
		}
	}
	va_end(ap);                        /* clean up when done */
	return nchar;
}

int main(void)
{
	minprintf("minprintf() output:\n");
	minprintf("%s\n", "hello, world");
	minprintf("%10s\n", "hello, world");
	minprintf("%.10s\n", "hello, world");
	minprintf("%-10s\n", "hello, world");
	minprintf("%.15s\n", "hello, world");
	minprintf("%-15s\n", "hello, world");
	minprintf("%15.10s\n", "hello, world");
	minprintf("%-15.10s\n", "hello, world");
	
	printf("\n");

	printf("printf() output:\n");
	printf("%s\n", "hello, world");
	printf("%10s\n", "hello, world");
	printf("%.10s\n", "hello, world");
	printf("%-10s\n", "hello, world");
	printf("%.15s\n", "hello, world");
	printf("%-15s\n", "hello, world");
	printf("%15.10s\n", "hello, world");
	printf("%-15.10s\n", "hello, world");
	return 0;
}


