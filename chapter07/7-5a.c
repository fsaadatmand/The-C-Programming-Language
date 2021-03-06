/*
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion.
 *
 * Note:  scanf and sscanf version
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP    100                   /* max size of operand or operator */
#define NUMBER   '0'                   /* signal that a number was found */
#define MAXVAL   100                   /* maximum depth of val stack */
#define BUFSIZE  100

/* functions */
void push(double);
double pop(void);
int getop(double *);
void ungets(char *);

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

/* getop: get next operator or numeric operand - scanf and sscanf version */
int getop(double *number)
{
	char c;
	int  n;                    /* number of consumed characters */
	int match;
	char s[MAXOP];

	if (scanf("%c", &c) < 0)
		return EOF;

	if (c == '\n')
		return c;

	ungetc(c, stdin);
	scanf("%s", s);            /* parse string from input stream */
	match = sscanf(s, "%lf %n", number, &n); /* scan number, consume trailing witespace */
	if (!match) {              /* not a number */
		sscanf(s, "%c", &c);
		if (strlen(s) > 1)     /* check for unread characters */
			ungets(s + 1);
		return c;
	}
	
	if (n != (int) strlen(s))  /* check unread char from match */
		ungets(s + n);

	return NUMBER;
}

/* ungets: push back s on input */
void ungets(char *s)
{
	int len;

	for (len = strlen(s); len >= 0; --len)
		ungetc(s[len], stdin);
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
