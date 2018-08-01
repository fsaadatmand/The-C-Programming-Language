/* 
 * program that removes all comments from a C program
 * note: full embeded comments with proceeding text are not supported yet.
 * By Faisal Saadatmand
 */

#include <stdio.h>

#define MAXLINE              1000
#define YES                     1
#define NO                      0
#define SLASH_ASTERISK          1
#define ASTERISK_SLASH          0
#define IN                      1
#define OUT                     0  

int  readline(char s[], int lim);
int  findComment(char line[], int notation);
int  delComment(char line[], char modLine[], int start, int end);

/* readline function: read a line into s, return length */
int readline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

/* findComment function: searches line[] for the first occurrence of the first
 * character of a C comment notation and returns the location on finding a single
 * line comment or -1 on failiure */
int findComment(char line[], int notation)
{
	int i, j;
	int quoteStart;           /* location of the start of the quotation mark */
	int quoteEnd;             /* location of the end of quotation mark */
	int location;             /* location of C comment notation */
	int comment[2];           /* notation type: start or end */
	int lookForQuote;         /* flag variable */

	location = quoteStart = quoteEnd = -1;
	/* set the appropriate notation */
	if (notation == SLASH_ASTERISK) {
		comment[0] = '/'; 
		comment[1] = '*';
	} else if (notation == ASTERISK_SLASH) {
		comment[0] = '*';
		comment[1] = '/';
	}

	lookForQuote  = YES;
	/* line[x - 1] check handles escape squences. It is unnecessary for the
	 * start of the quote but is added for the sake of correctness. */
	for (i = 0; line[i] != '\0'; ++i) {
		if (line[i] == comment[0] && line[i + 1] == comment[1])
			if (notation == ASTERISK_SLASH)
				location = i + 1;      /* end of comment including notation */
			else
				location = i;          /* start of comment including notation */
		if (line[i] == '\"' && line[i - 1] != '\\' && lookForQuote == YES) {
			quoteStart = i;
			for (j = i + 1; line[j] != '\0'; ++j)
				if (line[j] == '\"' && line[j - 1] != '\\')
					quoteEnd = j;
			lookForQuote = NO;
		}
	}
			
	/* check if notation is inside a double quotation marks */
	if (location >= 0 && quoteStart >= 0)
		if (location > quoteStart && location < quoteEnd)
			location = -1;       /* not a C comment */

	/* check if notation is inside a muli-line double quotation marks */
	if (location >= 0 && quoteStart >= 0 && quoteEnd < 0)
//		if (location < quoteStart)
			location = -1;       /* not a C comment */

	return location;
}

/* delComment function: deletes C comments from line stringn stores result in
 * modLine */
int delComment(char line[], char modLine[], int start, int end)
{
	int i, j;
	int len;
	int status;

	i = j = 0;

	/* no notation - delete entire line */
	if (start < 0 && end < 0)
		for (i = 0; line[i] != '\0'; ++i)
			modLine[i] = '\0';
	/* start but no end - delete rest of line */
	else if (start >= 0 && end < 0)
		for (i = 0; i < start; ++i)
			modLine[i] = line[i];
	/* end but no start - move text after comment to the begeining  of line */
	else if (start < 0 && end >= 0)
		for (j = end + 1; line[j] != '\0'; ++j)  {
			modLine[i] = line[j];
			++i;
		}
	/* full comment embedded - move text after comment to start location */
	else if (start >= 0 && end >= 0) {
		for (i = 0; i < start; ++i)
			modLine[i] = line[i];
		for (j = end + 1; line[j] != '\0'; ++j) {
			modLine[i] = line[j];
			++i;
		}
	}

	/* end of line formating */
	if (start < 0 && end < 0)
		modLine[0] = '\n';
	else if (start >= 0 && end < 0) {
		modLine[i] = '\n';
		modLine[i + 1] = '\0';
	} else 
		modLine[i] = '\0';

	/* status of the current deleted comment: single or multi-line */
	status = 0;
	if ((start >= 0 && end < 0) || (start < 0 && end < 0))
		status = 1;
	else if (start < 0 && end >= 0)
		status = 0;

	return status;
}

/* findCharcter function: counts the occurrence of a characters from symbol in
 * line and stores results in charsCount. len is the length of symbol array */
int findCharacter(char line[], char symbol[], int charsCount[], int len)
{
	int  i, j;
	static int quoteState;               /* double quote state flag */

	quoteState = OUT;
	for (i = 0; i <= len ; ++i)
		/* line[x - 1] check handles escape squences. */
		for (j = 0; line[j] != '\0'; ++j)
			if (quoteState == OUT && line[j] == '\"' && line[j - 1] != '\\')
				quoteState = IN;
			else if (quoteState == IN && line[j] == '\"' && line[j - 1] != '\\')
				quoteState = OUT;
			else if (line[j] == symbol[i] && line[j + 1] != '\'' && quoteState
					== OUT)
				++charsCount[i];
}

void checkSyntax(char symbol[], int charsCount[], int len)
{
	int i, syntaxError = 0;

	for (i = 0; i <= len; i += 2)
		if (charsCount[i] != charsCount[i + 1]) {
			printf("Syntax ERROR: unbalanced number of %c %c\n",
					symbol[i], symbol[i + 1]);
			syntaxError = 1;
		}
	if (syntaxError != 1)
		printf("Syntax check: no error found\n");
}
int main(void)
{
	int  len;                              /* current line length */
	int  start;                            /* comment's beginning */
	int  end;                              /* comment's end */
	int  status;                           /* multi-line comments flag */
	char line[MAXLINE];                    /* current input line */
	char modLine[MAXLINE];                 /* modified output line */
	int  charsCount[6];
	char symbol[6] = { '{', '}', '(', ')', '[', ']' };
	
	int i;
	for (len = 0; len <= 6 ; ++len)
		charsCount[len] = 0;

	status = 0;

	while ((len = readline(line, MAXLINE)) > 0) {

		start = findComment(line, SLASH_ASTERISK);
		end   = findComment(line, ASTERISK_SLASH);

		if (start < 0 && end < 0 && status == 0)    /* no comment found */
			findCharacter(line, symbol, charsCount, 5);
		else {
			status = delComment(line, modLine, start, end);
			findCharacter(modLine, symbol, charsCount, 5);
		}
	}
	checkSyntax(symbol, charsCount, 5);
	return 0;
}
