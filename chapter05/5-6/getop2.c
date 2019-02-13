/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getLine (chapter 1 and 4), atoi, itoa, and their variants (Chapters
 * 2, 3 and 4), reverse (Chapter 3), and strindex and gettop (Chapter 4)
 * By Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>              /* for atof() */
#include <ctype.h>
#include <string.h>              /* for strcmp() */
#include <math.h>                /* for math commands */

#define MAXLINE     1000
#define MAXOP       100          /* max size of operand or operator */
#define NUMBER      '0'          /* signal that a number was found */
#define MATH        '1'          /* signal that an operation was found */
#define END         0            /* signal EOF */
#define MAXVAL      100          /* maximum depth of val stack */
#define BUFSIZE     100
#define MATCH       0
#define MAXVAR      26           /* max number of variables */
#define TOP         val[sp - 1]  /* top of the stack element */ 

/* functions */
int    getop(char *);
int    getLine(char *, int);
void   push(double);
double pop(void);
void   printTop(void);
void   duplicateTop (void);
void   swapTopTwo(void);
void   clearStack(void);
void   storeVariable(double [], char);
void   fetchVariable(double [], char);
void   clearMemory(double [], int);

/* globals */
int    sp = 0;               /* next free stack position */
double val[MAXVAL];          /* value stack */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */
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
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand - pointer version */
int getop(char *s)
{
	static int    len;                     /* note static in type */
	static char   line[MAXLINE];           /* note static in type */
	static char   *pLine = line;           /* pointer to line */

	if (*pLine == '\0') {         /* check if the previous line was read completely */
		len = getLine(line, MAXLINE);	    /* read the next line */
		pLine = line;                       /* reset index */
		if (len < 0)                        /* check if there is a line */
			return END;
	}

	while (isblank(*pLine))                /* skip blanks */
		++pLine;

	if (*pLine == '-' && isdigit(*(pLine + 1)))  /* negative numbers */
			*s++ = *pLine++;
	
	if (!isdigit(*pLine) && !isalpha(*pLine) && *pLine != '.')
		return *pLine++;                   /* not a number */

	if (isalpha(*pLine)) {                 /* math functions and variables */
		while (isalpha(*pLine))
			*s++ = *pLine++;
		*s = '\0';
		return MATH;
	} else if (isdigit(*pLine))            /* collect number */
		while (isdigit(*pLine))
			*s++ = *pLine++;

	if( *pLine == '.')                     /* collect fraction part */
		while (isdigit(*pLine))
			*s++ = *pLine++;

	*s = '\0';
	return NUMBER;
}

/* getLine: get line into s, return length of s -- pointer version */
int getLine(char *s, int lim)
{
	int c, len;

	len = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		++len;
	}
	if ( c == '\n') {
		*s++ = c;
		++len;
	}
	*s = '\0';
	return len;
}

/* printTop: prints the top element in the stack without popping */
void printTop(void)
{
	if (sp > 0)
		printf("\t%.8g\n", TOP);
	else
		printf("stack is empty\n");
}

/* duplicateTop: duplicate the top element in the stack */
void duplicateTop (void)
{
	if (sp > 0)
		push(TOP);
}

/* swapTopTwos: swaps top two elements */
 void swapTopTwo(void)
 {
	 double top1, top2;

	 if (sp > 1) {
		 top1 = pop();
		 top2 = pop();
		 push(top1);
		 push(top2);
	 } else
		 printf("not enough elements\n");
 }

/* clear: clears the entire stack */
void clearStack(void)
{
	while (sp > 0)
		pop();
}

/* storeVariable: stores the value of a variable (a to z) to the corresponding
 * memory location in mem */
void storeVariable(double mem[], char variable)
{
	double value;

	if (variable == 'P') {          /* last printed value variable */
		value = lastPrint;          /* fetch last printed value value */
		mem[MAXVAR] = value;        /* last location is reserved for P */
	} else {
		pop();                        /* pop stored value by fetchVariable */
		value = pop();                /* variable value - top of the stack */
		variable = tolower(variable);
		mem[variable - 'a'] = value;
		push(value);
	}
}

/* fetchVariable: fetches variable value from memory and pushes to the top of
 * the stack */
void fetchVariable(double mem[], char variable)
{
	if (variable == 'P')          /* last printed value variable */
		push(mem[MAXVAR]);        /* last location is reserved for P */	
	else {
		variable = tolower(variable);
		push(mem[variable - 'a']); /* push value to the top of the stack */
	}
}

/* clearMemory: initializes values of mem to 0 */
void clearMemory(double mem[], int size)
{
	int i;

	for (i = 0; i <= size; ++i)
		mem[i] = 0;
}

/* reverse Polish Calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	static double mem[MAXVAR];          /* variables values */

	while ((type = getop(s)) != END) {
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
		case '$':
			storeVariable(mem, variable);
			break;
		case '\n':
			lastPrint = pop();
			printf("\t%.8g\n", lastPrint);
			storeVariable(mem, 'P');    /* store last printed value in P */
			break;
		case MATH:
			if (strlen(s) == 1) {
				variable = s[0];
				fetchVariable(mem, variable);
			} else if (strcmp(s, "sin") == MATCH)
				push(sin(pop()));
			else if (strcmp(s, "cos") == MATCH)
				push(cos(pop()));
			else if (strcmp(s, "exp") == MATCH)
				push(exp(pop()));
			else if (strcmp(s, "sqrt") == MATCH)
				push(sqrt(pop()));
			else if (strcmp(s, "pow") == MATCH) {
				op2 = pop();
				push(pow(pop(), op2));
			} else if (strcmp(s, "mc") == MATCH) {
				clearMemory(mem, MAXVAR);
				printf("memory cleared\n");		
			} else
				printf("error: unknown command %s\n", s);
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
