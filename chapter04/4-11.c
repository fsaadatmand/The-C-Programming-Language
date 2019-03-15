/*
 * Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint:
 * use an internal static variable.
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <ctype.h>
#include <string.h>          /* for strcmp() */
#include <math.h>            /* for math commands */

#define MAXOP   100          /* max size of operand or operator */
#define NUMBER  '0'          /* signal that a number was found */
#define MATH    '1'          /* signal that an operation was found */
#define MAXVAL  100          /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXVAR  26
#define TOP     val[sp - 1]  /* top element in stack */

/* functions */
int    getop(char []);
void   push(double);
double pop(void);
int    getch(void);
void   printTop(void);
void   duplicateTop(void);
void   swapTopTwo(void);
void   clearStack(void);
int    mathfunction(char []);
void   storeVariable(void);
void   fetchVariable(void);
void   clearMemory(void);

/* globals */
int    sp;                   /* next free stack position */
double val[MAXVAL];          /* value stack */
double mem[MAXVAR];          /* variables values */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */
int    stackcmd;             /* stack commands flag */
char   variable;             /* current input variable */ 
double lastPrint;            /* last printed value */

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
	static int prevC;        /* over-read character */

	(prevC > 0) ? (c = prevC) : (s[0] = c = getch());

	if (isblank(c)) {
		while (isblank(s[0] = c = getch()))
			;
		s[1] = '\0';
	}

	i = 0;
	if (c == '-')            /* check sign */
		if (!isdigit(s[++i] = c = getch())) {
			prevC = c;
			return s[0];     /* not a sign */
		}

	if (isalpha(c)) {        /*  math functions */
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		prevC = c;
		return MATH;
	}

	if (!isdigit(c) && c != '.') {
		prevC = 0;
		return c;            /* not a number */
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if( c == '.')            /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	prevC = c;
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

/* printTop: prints the top element in the stack */
void printTop(void)
{
	if (sp > 0) {
		printf("\t%.8g\n", TOP);
		stackcmd = 1;
	}
}

/* deleteTop: deletes the top element in the stack */
void duplicateTop(void)
{
	if (sp > 0) {
		push(TOP);
		printTop();
	}
}

/* swapTopTwo: swaps top two elements */
 void swapTopTwo(void)
 {
	 double top1, top2;

	 if (sp > 1) {
		 top1 = pop();
		 top2 = pop();
		 push(top1);
		 push(top2);
		 printTop();
	 }
}

/* clear: clears the entire stack */
void clearStack(void)
{
	while (sp > 0)
		pop();
	printTop();
}

/* mathf: call the appropriate math function according to value of s */
int mathfunction(char s[])
{
	double op2;

	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "cos") == 0)
		push(cos(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "sqrt") == 0)
		push(sqrt(pop()));
	else if (strcmp(s, "pow") == 0) {
		op2 = pop();
		push(pow(pop(), op2));
	} else
		return 0;
	return 1;
}

/* storeVariable: stores the value of a variable (a to z) to the corrosponding
 * memory location in mem */
void storeVariable(void)
{
	pop();                             /* pop stored value by fetchVariable */
	variable = tolower(variable);
	mem[variable - 'a'] = pop();       /* variable value - top of the stack */
	stackcmd = 1;                      /* skip pop print */
}

/* fetchVariable: fetches variable value from memory and pushes to the top of
 * the stack */
void fetchVariable(void)
{
	if (variable == 'R')
		push(lastPrint);
	else {
		variable = tolower(variable);
		push(mem[variable - 'a']);
	}
}

/* clearMemory: initializes values of mem to 0 */
void clearMemory(void)
{
	int i;

	for (i = 0; i <= MAXVAR; ++i)
		mem[i] = 0;
	printf("memory cleared\n");
	stackcmd = 1;                      /* skip pop print */
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
		case '!':
			printTop();
			break;
		case '#':
			duplicateTop();
			break;
		case '&':
			swapTopTwo();
			break;
		case '~':
			clearStack();
			break;
		case '=':
			storeVariable();
			break;
		case '\n':
			if (!stackcmd)
				printf("\t%.8g\n", lastPrint = pop());
			stackcmd = 0;
			break;
		case MATH:
			if (strlen(s) == 1) {
				variable = s[0];
				fetchVariable();
			} else if (strcmp(s, "mc") == 0)
				clearMemory();
			else if (!mathfunction(s))
				printf("error: unknown command %s\n", s);
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
