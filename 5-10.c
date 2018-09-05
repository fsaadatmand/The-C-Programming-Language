/*
 * Exercise 5-10. Write the program expr, which evalutes a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example,
 * 		expr 2 3 4 + *
 * evaluates 2 * (3 + 4).
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXOP  100
#define MAXVAL 100

/* function declarations */
void   push(double);
double pop(void);

/* external variables */
int    sp = 0;               /* next free stack position */
double val[MAXVAL];          /* value stack */

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
	int type, error = 0;
	double op2;

	if (argc < 4) {
		printf("Usage: expr operand1 operand2 operator operand3 operator ...\n");
		return -1;
	}

	while (--argc > 0) {
		++argv;                  /* skip program name */
		if (*(argv)[0] == '-' && isdigit(*(*argv + 1)))
			type = NUMBER;
		if (isdigit(*(argv)[0]))
			type = NUMBER;
		if (*(argv)[0] == '.' && isdigit(*(*argv + 1)))
			type = NUMBER;
		if (!isdigit(*(argv)[0]) && *(argv)[0] != '-' && *(argv)[0] != '.')
			type = *(argv)[0];
		switch (type) {
		case NUMBER:
			push(atof(*argv));
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
				printf("error: division by zero\n");
				error = 1;
			}
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((long) pop() % (long) op2);
			else {
				printf("error: division by zero\n");
				error = 1;
			}
			break;
		default:
			printf("error: unknown parameter\n");
			error = 1;
			break;
		}
	}
	if (!error)
		printf("%g\n", pop());
	return 0;
}
