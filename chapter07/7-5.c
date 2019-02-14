/*
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion.
 *
 * Note: Rewrote getop to use getchar and ungetc to peak at the next character
 * before calling scanf to handle the input and number conversion. getop takes
 * a double as an argument.
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP    100                   /* max size of operand or operator */
#define NUMBER   '0'                   /* signal that a number was found */
#define MAXVAL   100                   /* maximum depth of val stack */
#define BUFSIZE  100

/* functions */
void push(double);
double pop(void);
int getop(double *);

/* globals */
int sp = 0;                            /* next free stack position */
double val[MAXVAL];                    /* value stack */

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
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand - scanf version */
int getop(double *number)
{
	char c, sign;

	sign = 0;
	while (isblank(c = getchar()))     /* skip blank characters */
			;

	if (c == '+' || c == '-') {        /* check for sign */
		sign = c;
		if (!isdigit(c = getchar()) && c != '.') { /* take a peak */
			ungetc(c, stdin);          /* not a sign (possible operator) */
			return sign;               
		}
	}

	if (isdigit(c) || c == '.') {      /* take a peak */
		ungetc(c, stdin);              /* push c back onto input stream */
		if (sign > 0)
			ungetc(sign, stdin);
		if (scanf("%lf", number) == 1) /* scan and convert numbers */
			return NUMBER;
	}
	return c;
}

/* reverse polish calculator - scanf/sscanf version */
int main(void)
{
	int type;
	double op2, op;

	while ((type = getop(&op)) != EOF) {
		switch (type) {
		case (NUMBER):
			push(op);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero division\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %c\n", type);
			break;
		}
	}
	return 0;
}
