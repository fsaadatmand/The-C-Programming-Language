#include <stdio.h>

#define MAXLINE       1000         /* maximum input line length */

int readline(char s[], int lim);

/* readline function: read a line into s, return length */
int readline(char s[], int lim)
{
	int c, i, halt = 0;

	c = getchar();
	for (i = 0; halt == 0; ++i) {
		if (c == EOF)
			halt = 1;

		if (c == '\n')
			halt = 1;

		if (i > lim - 1)
			halt = 1;

		if (halt == 0) {
			s[i] = c;
			c = getchar();
		}		
	}
	--i;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

int main(void)
{
	int  len;                 /* current line length */
	char line[MAXLINE];       /* current input line */

	while ((len = readline(line, MAXLINE)) > 0) {
			printf("%s", line);
	}
	return 0;
}
