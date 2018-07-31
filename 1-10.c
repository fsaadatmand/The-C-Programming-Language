/* 
 * Program that replaces each tab with \t, each backspace with \b
 * and each backslash with \\
 */

#include <stdio.h>

#define YES 1
#define NO  0 

int main(void)
{
	int c, charReplaced; 

	while ((c = getchar()) != EOF) {
		charReplaced = NO;

		if (c == '\t') {
			printf("\\t");
			charReplaced = YES;
		}

		if (c == '\b') {
			printf("\\b");
			charReplaced = YES;
		}

		if (c == '\\') {
			printf("\\\\");
			charReplaced = YES;
		}

		if (charReplaced == NO)
			putchar(c);
	}

	return 0;
}
