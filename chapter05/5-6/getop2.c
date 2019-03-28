/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 *
 * Note: this is getop, getline version.
 *
 * By Faisal Saadatmand
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
#define TOP      val[sp - 1]  /* top element in stack */

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
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp;                 /* next free position in buf */
int    peak;                 /* flag: peak at top of the stack */
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
int getop(char *s)
{
	static int    len;                     /* note static in type */
	static char   line[MAXLINE];           /* note static in type */
	static char   *pline = line;
	char *var;

	if (*pline == '\0') {                  /* previous was read completely */
		len = getLine(line, MAXLINE);
		if (!len)
			return EOF;
		pline = line;                      /* rest index */
	}

	while (isblank(s[0] = *pline))         /* skip blanks */
		pline++;
	s[1] = '\0';

	if (*pline == '-' && !isdigit(*++s = *++pline))  /* check  sign */
		--pline;                           /* not a sign */
	
	if (isalpha(*pline)) {                 /* string command */
		var = s;
		while (isalpha(*pline))
			*++s = *++pline;
		*s = '\0';
		return (strlen(var) == 1) ? var[0] : NAME;
	}

	if (!isdigit(*pline) && *pline != '.')
		return *pline++;                   /* not a number */

	if (isdigit(*pline))                   /* collect number */
		while (isdigit(*pline))
			*++s = *pline++;

	if(*pline == '.')                     /* collect fraction part */
		while (isdigit(*pline))
			*++s = *pline++;

	*s = '\0';
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
	if (sp < 1)
		printf("stack empty\n");
	printf("\t%.8g\n", TOP);
}

/* duplicateTop: duplicate the top element in the stack */
void duplicateTop(void)
{
	double top;

	if (sp < 1)
		return;
	push(top = pop());
	push(top);
}

/* swapTopTwo: swaps top two elements */
 void swapTopTwo(void)
 {
	 double top1, top2;

	 if (sp < 2) {
		 if (sp == 1)
			 printf("error: 1 element in stack\n");
		 return;
	 }
	 top1 = pop();
	 top2 = pop();
	 push(top1);
	 push(top2);
}

/* clear: clears the entire stack */
void clearStack(void)
{
	while (sp > 1)
		pop();
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
//	if (isalpha(variable) && islower(variable)) {
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
				peak = 1;
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
		case '!':
			peak = 1;
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
			if (peak) {
				printTOP();
				peak = 0;
			} else
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
