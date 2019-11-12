/*
 * Exercise 4-10. An alternative organization uses getline to read an entire
 * input line; this makes getch and ungetch unnecessary. Revise the calculator
 * to use this approach.
 *
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>           /* for atof() */
#include <ctype.h>
#include <string.h>           /* for strcmp() */
#include <math.h>             /* for math commands */

#define MAXLINE  1000
#define MAXOP    100          /* max size of operand or operator */
#define NUMBER   '0'          /* signal that a number was found */
#define NAME     '1'          /* signal that a string command was found */
#define MAXVAL   100          /* maximum depth of val stack */
#define BUFSIZE  100
#define MAXVAR   26

/* functions */
int    getop(char []);
int    getLine(char [], int);
void   push(double);
double pop(void);
void   printTOP(void);
void   duplicateTop(void);
void   swapTopTwo(void);
void   clearStack(void);
int    mathfunction(char []);
void   storeVariable(void);
void   fetchVariable(int var);
void   clearMemory(void);

/* globals */
int    sp;                   /* next free stack position */
double val[MAXVAL];          /* value stack */
double mem[MAXVAR];          /* variables values */
int    buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */
int    variable;             /* current input variable */ 
double printed;              /* last printed value */

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

/* getop: get next operator or numeric operand - getline version */
int getop(char s[])
{
	static int    i, len;                  /* note static in type */
	static char   line[MAXLINE];           /* note static in type */
	int           j; 

	if (i == len) {                        /* previous line read completely */
		len = getLine(line, MAXLINE);
		if (!len)
			return EOF;
		i = 0;                             /* reset line index */
	}

	j = 0;
	while (isblank(line[i]))                /* skip blanks */
		++i;

	if (line[i] == '-' && isdigit(line[i + 1]))  /*  sign */
			s[j++] = line[i++];
	
	if (isalpha(line[i])) {                 /* math functions and variables */
		while (isalpha(line[i]))
			s[j++] = line[i++];
		s[j] = '\0';
		return (strlen(s) == 1) ? s[0] : NAME;
	}

	if (!isdigit(line[i]) && line[i] != '.')
		return line[i++];                   /* not a number */

	if (isdigit(line[i]))                   /* collect number */
		while (isdigit(line[i]))
			s[j++] = line[i++];

	if( line[i] == '.')                     /* collect fraction part */
		while (isdigit(line[i]))
			s[j++] = line[i++];

	s[j] = '\0';
	return NUMBER;
}

/* getLine: get line into s, return length of s */
int getLine(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if ( c == '\n')
		s[i++] = c;

	s[i] = '\0';
	
	return i;
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

/* clear: clears the entire stack */
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

/* storeVariable: store variable value (a to z) to the corresponding
 * location in mem and push back to top of stack */
void storeVariable(void)
{
	if (variable >= 'a' && variable <= 'z') {
		pop();
		push(mem[variable - 'a'] = pop());
	} else
		printf("error: no variable name\n");
}

/* fetchVariable: fetch var value from mem and push on to value stack */
void fetchVariable(int var)
{
	push(mem[var - 'a']);
}

/* clearMemory: set values of mem to 0 */
void clearMemory(void)
{
	int i;

	for (i = 0; i <= MAXVAR; ++i)
		mem[i] = 0;
	printf("memory cleared\n");
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
			if (!strcmp(s, "lp")) {
				push(printed);
			} else if (!strcmp(s, "mc")) {
				clearMemory();
			} else if (!mathfunction(s))
				printf("error: unknown command %s\n", s);
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
		case '=':
			storeVariable();
			break;
		case '\n':
			printf("\t%.8g\n", printed = pop());
			break;
		default:
			if (islower(type))
				fetchVariable(type);
			else
				printf("error: unknown command %s\n", s);
			break;
		}
		variable = type;               /* remember variable */
	}
	return 0;
}
