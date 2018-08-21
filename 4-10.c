/*
 * Exercise 4-10: An alernate organization uses getline to read an entire input
 * line; this makes getch and ungetch unnecessary. Revise the calculator to us
 * this approach.
 * Faisal Saadatmand
 */

#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <ctype.h>
#include <string.h>          /* for strcmp() */
#include <math.h>            /* for math commands */

#define MAXLINE     1000
#define MAXOP       100          /* max size of operand or operator */
#define NUMBER      '0'          /* signal that a number was found */
#define MATH        '1'          /* signal that an operation was found */
#define END         0            /* singal EOF */
#define MAXVAL      100          /* maximum depth of val stack */
#define BUFSIZE     100
#define MATCH       0
#define MAXVAR      26           /* max number of variables */
#define TOP         val[sp - 1]  /* top of the stack element */ 

/* function decleration */
int    getop(char []);
int    readline(char s[], int lim);
void   push(double);
double pop(void);
void   printTop(void);
void   duplicateTop (void);
void   swapTopTwo(void);
void   clearStack(void);
void   storeVariable(double mem[], char variable);
void   fetchVariable(double mem[], char variable);
void   clearMemory(double mem[], int size);

/* external variables */
char   previousLine[MAXLINE];
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

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	static int    i, len;                  /* note static in type */
	static char   line[MAXLINE];           /* note static in type */
	int           j; 

	if (i == len) {          /* check if the previous line is read completely */
		len = readline(line, MAXLINE);	    /* read the next line */
		i = 0;                              /* reset index */
		if (len < 0)                        /* line to read */
			return END;
	}

	j = 0;
	while (isblank(line[i]))                /* skip blanks */
		++i;

	if (line[i] == '-' && isdigit(line[i + 1]))  /* negative numbers */
			s[j++] = line[i++];
	
	if (!isdigit(line[i]) && !isalpha(line[i]) && line[i] != '.')
		return line[i++];                   /* not a number */

	if (isalpha(line[i])) {                 /* math functions and variables */
		while (isalpha(line[i]))
			s[j++] = line[i++];
		s[j] = '\0';
		return MATH;
	} else if (isdigit(line[i]))            /* collect number */
		while (isdigit(line[i]))
			s[j++] = line[i++];

	if( line[i] == '.')                     /* collect fraction part */
		while (isdigit(line[i]))
			s[j++] = line[i++];

	s[j] = '\0';
	return NUMBER;
}

/* readline: get line into s, return length of s */
int readline(char s[], int lim)
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
			}
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
