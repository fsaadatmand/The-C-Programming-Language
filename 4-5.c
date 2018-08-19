/* 
 * Exercise 4-5. Add commands to library functions like sin, exp and pow. see
 * <math.h> in Appendix B, Section 4.
 Faisal Saadatmand
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
#define MATCH   0
#define TOP     val[sp - 1]  /* top of the stack element */ 

/* function decleration */
int    getop(char []);
void   push(double);
double pop(void);
int    getch(void);
void   ungetch(int);
void   printTop(void);
void   duplicateTop(void);
void   swapTopTwo(void);
void   clearStack(void);

/* external variables */
int    sp = 0;               /* next free stack position */
double val[MAXVAL];          /* value stack */
char   buf[BUFSIZE];         /* buffer from ungetch */
int    bufp = 0;             /* next free position in buf */
int    sign = 1;             /* positive or negative */

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
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
	s[1] = '\0';

	if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-')
		return c;                           /* not a number */

	if (c == '-') {                         /* negative numbers provision */
		if (isdigit(s[0] = c = getch()))    /* peak at the next character */
			sign = -1;
		 else {                             /* not a negative number */
			ungetch(c);                     /* push char back for next cycle */
			return '-';
		}
	}

	i = 0;
	if (isalpha(c)) {                       /* math functions and variables */
		s[i++] = c;
		while (isalpha(s[i] = c = getch()))
			++i;
		s[i] = '\0';
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

/* printTop: prints the top element in the stack */
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

/* swapTopTwo: swaps top two elements */
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

/* reverse Polish Calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

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
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		case MATH:
			if (strcmp(s, "sin") == MATCH)
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
			}
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
