/*
 * Exercise 4-6. Add commands for handling variables. (it's easy to provide
 * twenty-six variables with single-letter names). Add a variable for most
 * recently printed value.
 Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <ctype.h>
#include <string.h>          /* for strcmp() */
#include <math.h>            /* for math commands */

#define MAXOP       100          /* max size of operand or operator */
#define NUMBER      '0'          /* signal that a number was found */
#define MATH        '1'          /* signal that an operation was found */
#define MAXVAL      100          /* maximum depth of val stack */
#define BUFSIZE     100
#define MATCH       0
#define MAXVAR      26
#define TOP         val[sp - 1]  /* top of the stack element */ 

/* function decleration */
int    getop(char []);
void   push(double);
double pop(void);
int    getch(void);
void   ungetch(int);
void   printTop(void);
void   duplicateTop (void);
void   swapTopTwo(void);
void   clearStack(void);
void   storeVariable(double mem[], char variable);
void   fetchVariable(double mem[], char variable);
void   clearMemory(double mem[], int size);

/* external variables */
int    sp = 0;               /* next free stack position */
double val[MAXVAL];          /* value stack */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */
int    sign = 1;             /* positive or negative */
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

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c, nextC;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (c == '-') {                        /* possible negative number */
		if (isdigit(nextC = getch())) {    /* peak at the next character */
			s[0] = c = nextC;              /* a negative number */
			sign = -1;                     /* set sign */
		} else if (nextC != EOF)           /* an operator, let c fall-through */
			ungetch(nextC);                /* push back nextC onto input */
	}

	if (!isdigit(c) && !isalpha(c) && c != '.')
		return c;                           /* not a number */

	i = 0;
	if (isalpha(c)) {                       /* math functions and variables */
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';

		if (c != EOF)
			ungetch(c);
		return MATH;
	}

	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if( c == '.')            /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';

	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void)              /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)          /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* printTop: prints the top element in the stack without poping */
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

/* storeVariable: stores the value of a variable (a to z) to the corrosponding
 * memory location in mem */
void storeVariable(double mem[], char variable)
{
	double value;

	if (variable == 'P') {          /* last printed value variable */
		value = lastPrint;          /* fetch last printed value value */
		mem[MAXVAR] = value;        /* last location is reserved for P */
	} else {
		pop();                        /* pop stored value by fetVariable */
		value = pop();                /* variable value - top of the stack */
		variable = tolower(variable);
		mem[variable - 'a'] = value;
		push(value);
	}
}

/* fetchVariable: fetches variable value from mempry and pushes to the top of
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

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(sign * atof(s));
			sign = 1;
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
