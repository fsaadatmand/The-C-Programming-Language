/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example,
 *
 * 		expr 2 3 4 + *
 *
 * evaluates 2 * (3 + 4).
 *
 * By Faisal Saadatmand
 */

/* NOTE: * and % must be included in equation marks at the command prompt,
 * otherwise they will be interpreted by the shell as wildcard characters */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXVAL 100

/* functions */
void push(double);
double pop(void);

/* globals */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int main(int argc, char *argv[])
{
	int type;
	double num, op2;

	if (argc < 4) {
		printf("Usage: %s <expr>...\n", *argv);
		return -1;
	}

	while (--argc > 0) {
		++argv;           /* skip program name */
		if ((num = atof(*argv)))
			type = NUMBER;
		else
			type = **argv; /* first character in *argv string */
		switch (type) {
		case NUMBER:
			push(num);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else {
				printf("error: zero divisor\n");
				argc = 1;
			}
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((long) pop() % (long) op2);
			else {
				printf("error: zero divisor\n");
				argc = 1;
			}
			break;
		default:
			printf("error: unknown command %s\n", *argv);
			argc = 1;
			break;
		}
	}
	printf(" %.8g\n", pop()); /* print result */
	return 0;
}
