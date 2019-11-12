/* 
 * Exercise 4-5. Add access to library functions like sin, exp and pow. see
 * <math.h> in Appendix B, Section 4.
 *
 Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>           /* for atof() */
#include <ctype.h>
#include <string.h>           /* for strcmp() */
#include <math.h>             /* for math commands */

#define MAXOP    100          /* max size of operand or operator */
#define NUMBER   '0'          /* signal that a number was found */
#define NAME     '1'          /* signal that a string command was found */
#define MAXVAL   100          /* maximum depth of val stack */
#define BUFSIZE  100

/* functions */
int    getop(char []);
void   push(double);
double pop(void);
int    getch(void);
void   ungetch(int);
void   printTOP(void);
void   duplicateTop(void);
void   swapTopTwo(void);
int    mathfunction(char []);

/* globals */
int    sp;                   /* next free stack position */
double val[MAXVAL];          /* value stack */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */

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

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	i = 0;
	if (c == '-')                      /* check sign */
		if (!isdigit(s[++i] = c = getch())) {
			ungetch(c);                    
			c = s[0];                  /* not a sign */
		}

	if (isalpha(c)) {                  /* string command */
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		ungetch(c);
		return NAME;
	}

	if (!isdigit(c) && c != '.')
		return c;                      /* not a number */

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if( c == '.')                      /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';

	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* printTOP: print top of the stack without pop */
void printTOP(void)
{
	double top;

	top = pop();
	printf("\t%.8g\n", top);
	push(top);
}

/* duplicateTop: duplicate the top element in the stack */
void duplicateTop(void)
{
	double top;

	push(top = pop());
	push(top);
}

/* swapTopTwo: swaps top two elements */
 void swapTopTwo(void)
 {
	 double top1, top2;

	 top1 = pop();
	 top2 = pop();
	 push(top1);
	 push(top2);
}

/* clearStack: clear the stack */
void clearStack(void)
{
	sp = 0;
}

/* mathfunction: call the appropriate math function according to value of s,
 * return 1 on success 0 on failure. */
int mathfunction(char s[])
{
	double op2;

	if (!strcmp(s, "sin"))
		push(sin(pop()));
	else if (!strcmp(s, "cos"))
		push(cos(pop()));
	else if (!strcmp(s, "exp"))
		push(exp(pop()));
	else if (!strcmp(s, "sqrt"))
		push(sqrt(pop()));
	else if (!strcmp(s, "pow")) {
		op2 = pop();
		push(pow(pop(), op2));
	} else
		return 0;
	return 1;
}

/* reverse Polish Calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case NAME:
			if (!mathfunction(s))
				printf("error: unkown command %s\n", s);
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
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((long) pop() % (long) op2);
			else
				printf("error: zero divisor\n");
			break;
		case '?':
			printTOP();
			break;
		case 'd':
			duplicateTop();
			break;
		case 's':
			swapTopTwo();
			break;
		case 'c':
			clearStack();
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
